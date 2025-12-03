/*

    Jubi Physics Library
    --------------------

    A simple 2D physics library for C/C++ projects.

    Created by Avery | GitHub: @Avery-Personal

    License: ALLPU License

===========================================================
                      VERSION INFORMATION

Jubi Version: 0.1.5
C Language Standard: C99
C++ Language Standard: C++98 or C++20

===========================================================
                     PROJECT INFORMATION

Project Description: A simple 2D physics library for C/C++ projects. It provides basic physics simulation features such as rigid body dynamics, collision detection, and response. The library is designed to be lightweight and easy to integrate into existing projects. It supports various shapes like circles and boxes, and allows for the creation of dynamic and static bodies within a world.
Project Status: Early Development | IN DEVELOPMENT

===========================================================
                     LICENSE INFORMATION

The following software is protected under the ALLPU license.
More detailed information is present at the root LICENSE
file AND OR the end of the file.

*/

#ifndef JUBI_H
#define JUBI_H

#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
    extern "C" {
#endif

#define JUBI_VERSION_MAJOR 0
#define JUBI_VERSION_MINOR 1
#define JUBI_VERSION_PATCH 2

#define JUBI_MAX_BODIES 1024
#define JUBI_MAX_SHAPES 2048

#define GRAVITY 9.81f
#define AIR_RESISTANCE 0.01f
#define FRICTION 0.1f

#define TIME_STEP 0.016f // ~60 FPS
#define TIME_STEP_120 0.008f // ~120 FPS

#define PI 3.14159265358979323846

typedef enum {
    JUBI_SUCCESS = 0,

    JUBI_ERROR_NULL_WORLD,
    JUBI_ERROR_WORLD_CORRUPTED,
    JUBI_ERROR_WORLD_DESTROYED,
    JUBI_ERROR_WORLD_FULL,
    JUBI_ERROR_NULL_BODY,
    JUBI_ERROR_BODY_NOT_IN_WORLD,

    JUBI_ERROR_UNKNOWN = -1,
} JubiResult;

typedef enum {
    SHAPE_CIRCLE,
    SHAPE_BOX
} Shape2D;

typedef enum {
    BODY_STATIC,
    BODY_DYNAMIC
} BodyType2D;

typedef struct {
    float x;
    float y;
} Vector2;

// Collision Helpers

typedef struct {
    Vector2 Min;
    Vector2 Max;
} AABB;

typedef struct {
    Vector2 Center;
    float Radius;
} Circle2D;

// Forward Declarations

typedef struct JubiWorld2D JubiWorld2D;

typedef struct {
    Vector2 Position;
    Vector2 Velocity;
    Vector2 _Size;

    Shape2D Shape;
    BodyType2D Type;
    float Mass;

    int Index; // Index in world (-1 if raw)
    JubiWorld2D *WORLD;
} Body2D;

struct JubiWorld2D {
    Body2D Bodies[JUBI_MAX_BODIES];
    
    int BodyCount;
    float Gravity;

    int Destroyed; // 0 = Valid, 1 = Destroyed
};

// Jubi Global Helpers

#define JUBI_SUCCESSFUL(Result) ((Result) == JUBI_SUCCESS)

// Jubi Functions

// World Management

JubiWorld2D Jubi_CreateWorld2D();
void Jubi_ClearWorld2D(JubiWorld2D *WORLD);
void Jubi_DestroyWorld2D(JubiWorld2D *WORLD);
int Jubi_WorldIsDestroyed(JubiWorld2D *WORLD);
int Jubi_IsWorldValid(JubiWorld2D *WORLD);

int Jubi_GetBodyIndex(JubiWorld2D *WORLD, Body2D *BODY);
int Jubi_IsBodyInWorld(JubiWorld2D *WORLD, Body2D *BODY);
int Jubi_AddBodyToWorld(JubiWorld2D *WORLD, Body2D *BODY);
int Jubi_RemoveBodyFromWorld(JubiWorld2D *WORLD, Body2D *BODY);

void Jubi_StepWorld2D(JubiWorld2D *WORLD, float DeltaTime);

// Vector2 Math

Vector2 JVector2_Add(Vector2 A, Vector2 B);
Vector2 JVector2_Subtract(Vector2 A, Vector2 B);
Vector2 JVector2_Multiply(Vector2 A, Vector2 B);
Vector2 JVector2_Divide(Vector2 A, Vector2 B);

Vector2 JVector2_Scale(Vector2 A, float Scalar);
float JVector2_Dot(Vector2 A, Vector2 B);
float JVector2_Cross(Vector2 A, Vector2 B);
Vector2 JVector2_Normalize(Vector2 A);

float JVector2_Length(Vector2 A);
float JVector2_Distance(Vector2 A, Vector2 B);
Vector2 JVector2_Direction(Vector2 A, Vector2 B);

Vector2 JVector_Project(Vector2 A, Vector2 B);
Vector2 JVector2_Reflect(Vector2 A, Vector2 NORMAL);
Vector2 JVector2_Perpendicular(Vector2 A);

float JClamp(float Value, float MIN, float MAX);

// Vector2 Initializers

Body2D JBody2D_Init(Vector2 Position, Vector2 Size, Shape2D Shape, BodyType2D Type, float Mass);
Body2D JBody2D_CreateBox(JubiWorld2D *WORLD, Vector2 Position, Vector2 Size, BodyType2D Type, float Mass);

// Vector2 Physics

Vector2 JVector2_ApplyGravity(Body2D *Body, float DeltaTime);

// Vector2 Collision Detection

int JCollision_AABBvsAABB(const AABB A, const AABB B);
int JCollision_CirclevsCircle(Circle2D A, Circle2D B);
int JCollision_AABBvsCircle(AABB A, Circle2D B);

void JCollision_ResolveAABBvsAABB(Body2D *A, Body2D *B);

#ifdef JUBI_IMPLEMENTATION
    // Implementation

    JubiWorld2D Jubi_CreateWorld2D() {
        JubiWorld2D WORLD;

        WORLD.BodyCount = 0;
        WORLD.Gravity = GRAVITY;
        WORLD.Destroyed = 0;

        return WORLD;
    }

    void Jubi_ClearWorld2D(JubiWorld2D *WORLD) {
        if (WORLD == NULL) return;
        if (WORLD -> Destroyed) return;

        WORLD -> BodyCount = 0;
    }

    void Jubi_DestroyWorld2D(JubiWorld2D *WORLD) {
        if (WORLD == NULL) return;
        if (WORLD -> Destroyed) return;

        for (int i = 0; i < JUBI_MAX_BODIES; ++i) {
            WORLD -> Bodies[i] = (Body2D){0};
        }

        WORLD -> BodyCount = 0;
        WORLD -> Gravity = 0.0f;
        WORLD -> Destroyed = 1;
    }

    int Jubi_WorldIsDestroyed(JubiWorld2D *WORLD) {
        if (WORLD == NULL) return 1;

        return WORLD -> Destroyed != 0;
    }

    int Jubi_IsWorldValid(JubiWorld2D *WORLD) {
        if (WORLD == NULL) return -1;
        if (WORLD -> BodyCount < 0) return -2;
        if (WORLD -> BodyCount > JUBI_MAX_BODIES) return -3;
        if (WORLD -> Destroyed) return -4;

        return 1;
    }

    JubiResult Jubi_GetWorldError(int WORLD_VALIDITY) {
        if (WORLD_VALIDITY == 1)
            return JUBI_SUCCESS;
        if (WORLD_VALIDITY == -1)
            return JUBI_ERROR_NULL_WORLD;
        if (WORLD_VALIDITY == -2)
            return JUBI_ERROR_WORLD_CORRUPTED;
        if (WORLD_VALIDITY == -3)
            return JUBI_ERROR_WORLD_FULL;
        if (WORLD_VALIDITY == -4)
            return JUBI_ERROR_WORLD_DESTROYED;
        if (WORLD_VALIDITY == -5)
            return JUBI_ERROR_UNKNOWN;

        return JUBI_SUCCESS;
    }

    // Global Helpers

    int Jubi_GetBodyIndex(JubiWorld2D *WORLD, Body2D *BODY) {
        if (Jubi_IsWorldValid(WORLD) == 0 || BODY == NULL) return -1;

        for (int i = 0; i < WORLD -> BodyCount; i++)
            if (&WORLD -> Bodies[i] == BODY)
                return i;

        return -1;
    }

    int Jubi_IsBodyInWorld(JubiWorld2D *WORLD, Body2D *BODY) {
        if (Jubi_IsWorldValid(WORLD) == 0 || BODY == NULL) return -1;

        for (int i = 0; i < WORLD -> BodyCount; i++)
            if (&WORLD -> Bodies[i] == BODY)
                return 1;

        return 0;
    }

    int Jubi_AddBodyToWorld(JubiWorld2D *WORLD, Body2D *BODY) {
        if (Jubi_IsWorldValid(WORLD) == 0) return -1;

        int INDEX = WORLD -> BodyCount++;

        WORLD -> Bodies[INDEX] = *BODY;
        WORLD -> Bodies[INDEX].WORLD = WORLD;
        WORLD -> Bodies[INDEX].Index = INDEX;

        return INDEX;
    }

    int Jubi_RemoveBodyFromWorld(JubiWorld2D *WORLD, Body2D *BODY) {
        if (Jubi_IsWorldValid(WORLD) == 0) return -1;

        int INDEX = Jubi_GetBodyIndex(WORLD, BODY);
        if (INDEX < 0) return 0;

        for (int i = INDEX; i < WORLD -> BodyCount - 1; i++) {
            WORLD -> Bodies[i] = WORLD -> Bodies[i + 1];
            WORLD -> Bodies[i].Index = i;
        }

        WORLD -> Bodies[WORLD -> BodyCount - 1] = (Body2D){0};
        WORLD -> BodyCount--;

        return 1;
    }

    // Vector2 Math

    Vector2 JVector2_Add(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        RESULT.x = A.x + B.x;
        RESULT.y = A.y + B.y;

        return RESULT;
    }

    Vector2 JVector2_Subtract(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        RESULT.x = A.x - B.x;
        RESULT.y = A.y - B.y;

        return RESULT;
    }

    Vector2 JVector2_Multiply(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        RESULT.x = A.x * B.x;
        RESULT.y = A.y * B.y;

        return RESULT;
    }

    Vector2 JVector2_Divide(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        RESULT.x = A.x / B.x;
        RESULT.y = A.y / B.y;

        return RESULT;
    }

    float JVector2_Length(Vector2 A) {
        return sqrt(A.x * A.x + A.y * A.y);
    }

    Vector2 JVector2_Scale(Vector2 A, float Scalar) {
        Vector2 RESULT;

        RESULT.x = A.x * Scalar;
        RESULT.y = A.y * Scalar;

        return RESULT;
    }

    float JVector2_Dot(Vector2 A, Vector2 B) {
        return A.x * B.x + A.y * B.y;
    }

    float JVector2_Cross(Vector2 A, Vector2 B) {
        return A.x * B.y - A.y * B.x;
    }

    Vector2 JVector2_Normalize(Vector2 A) {
        float LENGTH = sqrt(A.x * A.x + A.y * A.y);

        A.x /= LENGTH;
        A.y /= LENGTH;

        return A;
    }

    float JVector2_Distance(Vector2 A, Vector2 B) {
        float RESULTX = B.x - A.x;
        float RESULTY = B.y - A.y;

        return sqrt(RESULTX * RESULTX + RESULTY * RESULTY);
    }

    Vector2 JVector2_Direction(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        RESULT.x = B.x - A.x;
        RESULT.y = B.y - A.y;

        float LENGTH = sqrt(RESULT.x * RESULT.x + RESULT.y * RESULT.y);

        if (LENGTH == 0)
            return (Vector2){0, 0};

        RESULT.x /= LENGTH;
        RESULT.y /= LENGTH;

        return RESULT;
    }

    Vector2 JVector_Project(Vector2 A, Vector2 B) {
        Vector2 RESULT;

        float DOT_PRODUCT = JVector2_Dot(A, B);
        float B_LENGTH_SQUARED = JVector2_Dot(B, B);

        if (B_LENGTH_SQUARED == 0)
            return (Vector2){0, 0};

        float SCALAR = DOT_PRODUCT / B_LENGTH_SQUARED;

        RESULT.x = B.x * SCALAR;
        RESULT.y = B.y * SCALAR;

        return RESULT;
    }

    Vector2 JVector2_Reflect(Vector2 A, Vector2 NORMAL) {
        Vector2 RESULT;
        
        float DOT_PRODUCT = JVector2_Dot(A, NORMAL);

        RESULT.x = A.x - 2 * DOT_PRODUCT * NORMAL.x;
        RESULT.y = A.y - 2 * DOT_PRODUCT * NORMAL.y;

        return RESULT;
    }

    Vector2 JVector2_Perpendicular(Vector2 A) {
        Vector2 RESULT;
        
        RESULT.x = -A.y;
        RESULT.y = A.x;

        return RESULT;
    }
    
    float JClamp(float Value, float MIN, float MAX) {
        if (Value < MIN) return MIN;
        if (Value > MAX) return MAX;

        return Value;
    }

    // Vector2 Initializers

    Body2D JBody2D_Init(Vector2 Position, Vector2 Size, Shape2D Shape, BodyType2D Type, float Mass) {
        Body2D BODY;

        BODY.Position = Position;
        BODY.Velocity = (Vector2){0, 0};
        BODY._Size = Size;
        BODY.Shape = Shape;
        BODY.Type = Type;
        BODY.Mass = Mass;

        BODY.Index = -1;
        BODY.WORLD = NULL;

        return BODY;
    }

    Body2D JBody2D_CreateBox(JubiWorld2D *WORLD, Vector2 Position, Vector2 Size, BodyType2D Type, float Mass) {
        Body2D BODY = JBody2D_Init(Position, Size, SHAPE_BOX, Type, Mass);

        if (Jubi_IsWorldValid(WORLD)) {
            int INDEX = Jubi_AddBodyToWorld(WORLD, &BODY);
            if (INDEX < 0) return (Body2D){0};  

            BODY.Index = INDEX;
            BODY.WORLD = WORLD;
        }

        return BODY;
    }

    // Vector2 Physics

    Vector2 JVector2_ApplyGravity(Body2D *Body, float DeltaTime) {
        if (Body -> Type == BODY_DYNAMIC) {
            Vector2 GRAVITY_FORCE = JVector2_Scale((Vector2){0, GRAVITY}, DeltaTime);

            Body -> Velocity = JVector2_Add(Body->Velocity, GRAVITY_FORCE);
        }

        return Body -> Velocity;
    }

    // Vector2 Collision Detection

    int JCollision_AABBvsAABB(const AABB A, const AABB B) {
        if (A.Min.x < B.Max.x && A.Max.x > B.Min.x && A.Min.y < B.Max.y && A.Max.y > B.Min.y)
            return 1;

        return 0;
    }

    int JCollision_CirclevsCircle(Circle2D A, Circle2D B) {
        float DISTANCE = JVector2_Distance(A.Center, B.Center);
        float RADIUS_SUM = A.Radius + B.Radius;

        if (DISTANCE < RADIUS_SUM)
            return 1;

        return 0;
    }

    int JCollision_AABBvsCircle(AABB A, Circle2D B) {
        float CLOSEST_X = JClamp(B.Center.x, A.Min.x, A.Max.x);
        float CLOSEST_Y = JClamp(B.Center.y, A.Min.y, A.Max.y);

        float DISTANCE_X = B.Center.x - CLOSEST_X;
        float DISTANCE_Y = B.Center.y - CLOSEST_Y;

        float DISTANCE_SQUARED = (DISTANCE_X * DISTANCE_X) + (DISTANCE_Y * DISTANCE_Y);
        float RADIUS_SQUARED = B.Radius * B.Radius;

        if (DISTANCE_SQUARED < RADIUS_SQUARED)
            return 1;

        return 0;
    }

    void JCollision_ResolveAABBvsAABB(Body2D *A, Body2D *B) {
        A -> Velocity = (Vector2){0, 0};
        B -> Velocity = (Vector2){0, 0};
    }

    int JCollision_ResolveCirclevsCircle(Body2D *A, Body2D *B) {
        A -> Velocity = (Vector2){0, 0};
        B -> Velocity = (Vector2){0, 0};
    }

    int JCollision_ResolveAABBvsCircle(Body2D *A, Body2D *B) {
        A -> Velocity = (Vector2){0, 0};
        B -> Velocity = (Vector2){0, 0};
    }

#endif // JUBI_IMPLEMENTATION

#ifdef __cplusplus
    }
#endif

#endif
