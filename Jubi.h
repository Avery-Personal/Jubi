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
#define TIME_STEP 0.016f // ~60 FPS
#define TIME_STEP_120 0.008f // ~120 FPS

#define PI 3.14159265358979323846

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

typedef struct {
    Vector2 Position;
    Vector2 Velocity;
    Vector2 _Size;

    Shape2D Shape;
    BodyType2D Type;

    float Mass;
} Body2D;

typedef struct {
    Body2D Bodies[JUBI_MAX_BODIES];
    
    int BodyCount;
    float Gravity;

    int Destroyed; // 0 = Valid, 1 = Destroyed
} JubiWorld2D;

JubiWorld2D Jubi_CreateWorld2D();
void Jubi_ClearWorld2D(JubiWorld2D *WORLD);
void Jubi_DestroyWorld2D(JubiWorld2D *WORLD);
int Jubi_WorldIsDestroyed(JubiWorld2D *WORLD);

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

Vector2 JVector2_Gravity(float GravityStrength, float DeltaTime);

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

    Body2D JBody2D_CreateBox(Vector2 Position, Vector2 Size, BodyType2D Type, float Mass) {
        Body2D BODY;

        BODY.Position = Position;
        BODY._Size = Size;
        BODY.Velocity = (Vector2){0, 0};
        BODY.Shape = SHAPE_BOX;
        BODY.Type = Type;
        BODY.Mass = Mass;

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

#endif // JUBI_IMPLEMENTATION

#ifdef __cplusplus
    }
#endif

#endif
