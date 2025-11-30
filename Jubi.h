#ifndef JUBI_H
#define JUBI_H

#include <math.h>

#ifdef __cplusplus
    extern "C" {
#endif

#define JUBI_MAX_BODIES 1024
#define JUBI_MAX_SHAPES 2048

#define GRAVITYF 9.81f
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

    Body2D JBody2D_Create(Vector2 Position, Vector2 Size, BodyType2D Type, float Mass) {
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

    Vector2 JVector2_Gravity(float GravityStrength, float DeltaTime) {
        Vector2 RESULT = {0};

        RESULT.y = GravityStrength * DeltaTime;

        return RESULT;
    }    

#endif // JUBI_IMPLEMENTATION

#ifdef __cplusplus
    }
#endif

#endif
