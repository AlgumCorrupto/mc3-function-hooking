#include <types.h>
#include <mc3.h>
#include <sdk.h>

typedef struct{
    float p[3];
} Vec3;

typedef struct {
    // horizontal, 0
    // vertical, 1
    // depth, 2
    Vec3 m[4];
} Mat34;

static float bpm = 135.f;

static float sqrt(float x) {
    float result;

    // i dont have access to stdlib, neither does game has a sqrt function
    __asm__ volatile (
        "sqrt.s %0, %1"
        : "=f"(result)
        : "f"(x)
    );

    return result;
}


static inline float ease_in_out(float t, float strength)
{
    // strength = 1: linear
    // strength = 2: quadratic
    // strength = 3: cubic
    if (t < 0.5f)
        return 0.5f * powf(2.f * t, strength);
    else
        return 1.f - 0.5f * powf(2.f * (1.f - t), strength);
}

static Vec3 squash_stretch(float amount) {
    // amount = 1.0 -> normal
    // amount < 1.0 -> squash vertically
    // amount > 1.0 -> stretch vertically

    float horizontal = 1.f / sqrt(amount);
    return (Vec3){{horizontal, amount, horizontal}};
}

void bounce(char *a0) {

    u32 *skelly = *(u32 **)(a0 + 208);
    float *phase = (float *)(a0 + 212);

    if (!(*phase >= 0.f && *phase < 1.f))
        *phase = 0.f;

    Mat34 *local = (Mat34 *)skelly[1]; // the friggin local transform of the car

    float delta = 1.f / 30.f; // fuck your unstable framerates

    float frequency = bpm / 60.f;

    *phase += delta * frequency;

    if (*phase >= 1.f)
        *phase -= 1.f;

    float amount;

    if (*phase < 0.5f) {
        float t = *phase / 0.5f;
        t = t * t * (3.f - 2.f * t); // DONT FUCKIGN WORRY ABOUT APPLYING EASE-IN-OUT 2 TIMES
        t = ease_in_out(t, 3.0);

        amount = lerp_float(1.15f, 0.85f, t);
    } else {
        float t = (*phase - 0.5f) / 0.5f;

        t = ease_in_out(t, 3.0);
        amount = lerp_float(0.85f, 1.15f, t);
    }

    Vec3 scale = squash_stretch(amount);

    local->m[0].p[0] = scale.p[0];
    local->m[1].p[1] = scale.p[1];
    local->m[2].p[2] = scale.p[2];
}