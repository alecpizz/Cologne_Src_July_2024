#include "PhysicsManager.h"
#include "../Engine.h"

PhysicsManager::PhysicsManager()
{
    RegisterDefaultAllocator();

    Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedIMpl;)

    factory = new Factory();
    Factory::sInstance = factory;

    RegisterTypes();

    temp_allocator = new TempAllocatorImpl(10 * 1024 * 1024);

    job_system = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

    physics_system.Init(MaxBodies, NumBodyMutexes, MaxBodyPairs, MaxContactConstraints,
                        broad_phase_layer_interface, object_vs_broadphase_layer_filter,
                        object_vs_object_layer_filter);

    physics_system.SetBodyActivationListener(&body_activation_listener);

    physics_system.SetContactListener(&contact_listener);

    bodyInterface = &physics_system.GetBodyInterface();

    debugRenderer = new MyDebugRenderer();

    // make a floor yah!
    BoxShapeSettings floor_shape_settings(RVec3(100.0f, 1.0f, 100.0f));
    floor_shape_settings.SetEmbedded();

    ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
    ShapeRefC floor_shape = floor_shape_result.Get();

    BodyCreationSettings floor_settings(floor_shape, RVec3(0.0f, -2.0f, 0.0f), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
    floor = bodyInterface->CreateBody(floor_settings);
    bodyInterface->AddBody(floor->GetID(), EActivation::DontActivate);

    // make a cube yah! this is way less stupid than the other method lol
    BodyCreationSettings ball_settings(new BoxShape(RVec3(1.0f, 1.0f, 1.0f)), RVec3(0.0f, 10.0f, 0.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
    cube = bodyInterface->CreateAndAddBody(ball_settings, EActivation::Activate);
    bodyInterface->AddAngularImpulse(cube, Vec3(1000.0f, 1000.0f, 1000.0f));
    physics_system.OptimizeBroadPhase();

    // temp code
}

PhysicsManager::~PhysicsManager()
{
    bodyInterface->RemoveBody(floor->GetID());
    bodyInterface->DestroyBody(floor->GetID());
    floor = nullptr;

    bodyInterface->RemoveBody(cube);
    bodyInterface->DestroyBody(cube);
    UnregisterTypes();

    delete factory;
    factory = nullptr;
    Factory::sInstance = nullptr;
    bodyInterface = nullptr;

    delete temp_allocator;
    temp_allocator = nullptr;

    delete job_system;
    job_system = nullptr;
}

void PhysicsManager::TraceImpl(const char *inFMT, ...)
{
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);
    CG_CORE_TRACE(buffer);
}

void PhysicsManager::update(float dt)
{
    const int collisionSteps = 1;
    position = bodyInterface->GetCenterOfMassPosition(cube);
//    std::cout << "Position: " << ConvertToString(bodyInterface->GetCenterOfMassPosition(cube)).c_str() << std::endl;
    rotation = bodyInterface->GetRotation(cube);
    physics_system.Update(dt, collisionSteps, temp_allocator, job_system);
}

void PhysicsManager::postUpdate(glm::mat4 view, glm::mat4 project)
{
    debugRenderer->update(view, project);
    BodyManager::DrawSettings settings{};
    settings.mDrawShape = true;
    settings.mDrawShapeWireframe = true;
    physics_system.DrawBodies(settings, debugRenderer);
}


#ifdef JPH_ENABLE_ASSERTS
bool PhysicsManager::AssertFailedIMpl(const char *inExpression, const char *inMessage, const char *inFile, unsigned int inLine)
{
    std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << std::endl;
    return true;
}
#endif

bool ObjectLayerPairFilterImpl::ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const
{
    switch (inObject1)
    {
    case Layers::NON_MOVING:
        return inObject2 == Layers::MOVING;
    case Layers::MOVING:
        return true;
    default:
        JPH_ASSERT(false);
        return false;
    }
}

BPLayerInterfaceImpl::BPLayerInterfaceImpl()
{
    objectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    objectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
}

uint BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const
{
    return BroadPhaseLayers::NUM_LAYERS;
}

BroadPhaseLayer BPLayerInterfaceImpl::GetBroadPhaseLayer(ObjectLayer inLayer) const
{
    JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
    return objectToBroadPhase[inLayer];
}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char *BPLayerInterfaceImpl::GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const
{
    switch ((BroadPhaseLayer::Type)inLayer)
    {
    case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
        return "NON_MOVING";
    case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
        return "MOVING";
    default:
        JPH_ASSERT(false);
        return "INVALID";
    }
}
#endif

bool ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const
{
    switch (inLayer1)
    {
    case Layers::NON_MOVING:
        return inLayer2 == BroadPhaseLayers::MOVING;
    case Layers::MOVING:
        return true;
    default:
        JPH_ASSERT(false);
        return false;
    }
}

ValidateResult MyContactListener::OnContactValidate(const Body &inBody1, const Body &inBody2, RVec3Arg inBaseOffset, const CollideShapeResult &inCollisionResult)
{
    CG_CORE_INFO("Contact validate callback");
    return ValidateResult::AcceptAllContactsForThisBodyPair;
}

void MyContactListener::OnContactAdded(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &ioSettings)
{
    CG_CORE_INFO("Contact was added");
}

void MyContactListener::OnContactPersisted(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &ioSettings)
{
    CG_CORE_INFO("Contact was persisted");
}

void MyContactListener::OnContactRemoved(const SubShapeIDPair &inSubShapePair)
{
    CG_CORE_INFO("Contact was removed");
}

void MyBodyActivationListener::OnBodyActivated(const BodyID &inBodyID, uint64 inBodyUserData)
{
    CG_CORE_INFO("A body was activated");
}

void MyBodyActivationListener::OnBodyDeactivated(const BodyID &inBodyID, uint64 inBodyUserData)
{
    CG_CORE_INFO("A body fell asleep!");
}


