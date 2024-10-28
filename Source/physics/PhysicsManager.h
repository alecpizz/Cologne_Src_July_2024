#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "../cgpch.h"
#include "PhysicsDebugRenderer.h"


using namespace JPH;

JPH_SUPPRESS_WARNINGS

namespace Layers
{
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
};

namespace BroadPhaseLayers
{
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
};

class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override;
};

class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
    BPLayerInterfaceImpl();
    virtual uint GetNumBroadPhaseLayers() const override;
    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override;

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char *GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override;
#endif
private:
    BroadPhaseLayer objectToBroadPhase[Layers::NUM_LAYERS];
};

class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override;
};

class MyContactListener : public ContactListener
{
public:
    virtual ValidateResult OnContactValidate(const Body &inBody1, const Body &inBody2, RVec3Arg inBaseOffset, const CollideShapeResult &inCollisionResult) override;
    virtual void OnContactAdded(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &ioSettings) override;
    virtual void OnContactPersisted(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &ioSettings) override;
    virtual void OnContactRemoved(const SubShapeIDPair &inSubShapePair) override;
};

class MyBodyActivationListener : public BodyActivationListener
{
public:
    virtual void OnBodyActivated(const BodyID &inBodyID, uint64 inBodyUserData) override;
    virtual void OnBodyDeactivated(const BodyID &inBodyID, uint64 inBodyUserData) override;
};


class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();
    Body *floor;
    BodyID cube;
    BodyInterface *bodyInterface;
    static void TraceImpl(const char *inFMT, ...);
    void update(float dt);
    void postUpdate(glm::mat4 view, glm::mat4 project);
    Vec3 position;
    Quat rotation;
#ifdef JPH_ENABLE_ASSERTS
    static bool AssertFailedIMpl(const char *inExpression, const char *inMessage, const char *inFile, unsigned int inLine);
#endif
private:
    Factory *factory = nullptr;
    MyDebugRenderer *debugRenderer = nullptr;
    BPLayerInterfaceImpl broad_phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;
    const uint MaxBodies = 1024;
    const uint NumBodyMutexes = 0;
    const uint MaxBodyPairs = 1024;
    const uint MaxContactConstraints = 1024;
    PhysicsSystem physics_system;
    MyBodyActivationListener body_activation_listener;
    MyContactListener contact_listener;
    TempAllocatorImpl *temp_allocator;
    JobSystemThreadPool *job_system;
};


#endif