Request for comment: ???
Category: Documentation
Epitech Montpellier

                                                                    Sebastien Phelip
                                                                    Laurent Amat
                                                                    Benjamin Vic
                                                                    Etienne Licheron
                                                                    Adrien Zobiri
                                                                    November 2022


                        RType: Third year epitech project

Abstract

    This document describes the protocol used by the RType game. The RType it's a game
    who is a clone of the famous game R-Type. The game is a multiplayer game who is
    played by 1 to 4 players. The server can host several games at the same time.


Table of Contents

    1. Introduction .................................................... Line 34
    2. Architecture .................................................... Line 39
    3. ECS ............................................................. Line 44
        3 Entity ....................................................... Line 49
        3.1. Attribute ................................................. Line 54
        3.2. System .................................................... Line 58
    4. Tutorial ........................................................ Line 62



1. Introduction

    An ECS is a way to manage entities and their attributes. It's a way to make a game more modular and scalable. It's also a way to make the game more efficient by only rendering the entities that are visible on the screen.


2. Architecture

    The ECS works with 3 main managers : an EntityManager, an AttributeManager and a SystemManager. Also, an Coordinator will be used to manager those. It will map attributes on entities and systems to render certain attributes or entities.


3. ECS

    We will go through the 3 managers and how to use them with the coordinator. You will also have a better understanding of how you should think when you develop a game with an ECS.


    3.1. Entity

        An entity is a unique identifier. It's a number that will be used to identify an entity. In a game, an entity can be a player, a mob, a bullet, etc. It's a way to identify an object in the game. You can create an entity with the coordinator. It will register it, add a support to link attribute and systems to it.


    3.2 Attribute

        An attribute is a way to add data and specific behaviors on entity. On a player, it could be is health, or it's speed. On a bullet, it could be it's damage, or it's speed again. You can note that, both player and bullet have a speed attribute. It's a way to make the game more modular. You can create an attribute with the coordinator. It will register it, add a support to link it to an entity and a system to render it.

    3.3 Systems

        A system is a way to render attributes. It could move all entities that have a speed attribute. It's a way to make the game more scalable. You can create a system with the coordinator. It will register it, add a support to link it to an attribute and an entity to render it.

4. Tutorial

    We will design a simple program to render cubes that fall down in the air. We will teach you here how to use the ECS effectiently. We can start by defining some attributes for our cubes : a gravity, a body, and a transform (or speed). They will hold data for each entities (an cube will have a different velocity than an other cube)
    ```cpp
    struct Gravity {
        Vec3 force;
    };

    struct RigidBody {
        Vec3 velocity;
        Vec3 acceleration;
    };

    struct Transform {
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
    };
    ```
    Now, we can implement an rudimentary physics system. It will hold the logic of one, or more attributes.
    ```cpp
    extern RType::Shared::ECS::Coordinator globalCoordinator;

    void PhysicsSystem::update(float dt) // dt = delta time, and the class inherit from RType::Shared::ECS::System
    {
        for (auto const& entity : entities) { // entities is a vector of Entity, and is inherited from RType::Shared::ECS::System
            auto &rigidBody = globalCoordinator.getAttribute<RigidBody>(entity);
            auto &transform = globalCoordinator.getAttribute<Transform>(entity);
            auto const &gravity = globalCoordinator.getAttribute<Gravity>(entity);

            transform.position += rigidBody.velocity * dt; // We update the position of the cube
            rigidBody.velocity += gravity.force * dt; // We update the velocity of the cube
        }
    }
    ```
    Now, we can create our entities and add them to the coordinator. We will add to them the attributes we defined before and render them with the physics system.
    ```cpp
    RType::Shared::ECS::Coordinator globalCoordinator;

    int main(void)
    {
        globalCoordinator.init();
        globalCoordinator.registerAttribute<Gravity>();
        globalCoordinator.registerAttribute<RigidBody>();
        globalCoordinator.registerAttribute<Transform>();
        auto physicsSystem = globalCoordinator.registerSystem<PhysicsSystem>();

        RType::Shared::ECS::Signature signature;
        signature.set(globalCoordinator.getAttributeType<Gravity>());
        signature.set(globalCoordinator.getAttributeType<RigidBody>());
        signature.set(globalCoordinator.getAttributeType<Transform>());
        globalCoordinator.setSystemSignature<PhysicsSystem>(signature);

        std::default_random_engine generator;
        std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
        std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
        std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
        std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);
        float scale = randScale(generator);

        for (auto& entity : globalCoordinator.getEntities()) {
            entity = globalCoordinator.createEntity(); // create an entity

            globalCoordinator.addAttribute( // add gravity to it
                entity,
                Gravity{Vec3(0.0f, randGravity(generator), 0.0f)});

            globalCoordinator.addAttribute( // add rigidbody to it
                entity,
                RigidBody{
                    .velocity = Vec3(0.0f, 0.0f, 0.0f),
                    .acceleration = Vec3(0.0f, 0.0f, 0.0f)
                });

            globalCoordinator.addAttribute( // add transform to it
                entity,
                Transform{
                    .position = Vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
                    .rotation = Vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
                    .scale = Vec3(scale, scale, scale)
                });
        }

        float dt = 0.0f;
        while (!quit) {
            auto startTime = std::chrono::high_resolution_clock::now();
            physicsSystem->update(dt);
            auto stopTime = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
        }
    }
    ```
    The window should show 10,000 cubes (of different sizes & colors) falling under the influence of gravity with a black background. Circling back to the beginning about attributes also making complex behavior easier, we could easily flip our demo by not adding a RigidBody or a Gravity to the cubes, and instead adding them to the camera, so the camera fall down while the cubes stay in place. This is a very simple example, but it shows how attributes can be used to create complex behavior from simple parts.
