#include <types.h>
#include <mc3.h>
#include <sdk.h>

// skelly = a0 + 208
// then skelly[1]
// ts is the local transform

typedef struct{
    float p[3];
} Vec3;

typedef struct {
    // horizontal
    // vertical
    // depth
    Vec3 m[4];
} Mat34;

static float bpm = 135.f;

float sqrt(float x) {
    float result;

    __asm__ volatile (
        "sqrt.s %0, %1"
        : "=f"(result)
        : "f"(x)
    );

    return result;
}

Vec3 squash_stretch(float amount) {
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

    Mat34 *local = (Mat34 *)skelly[1]; // transformação local do chassi

    float delta = 1.f / 30.f;
    float frequency = bpm / 60.f;

    *phase += delta * frequency;

    if (*phase >= 1.f)
        *phase -= 1.f;

    float amount;

    if (*phase < 0.5f) {
        // Squash: ease-in-out
        float t = *phase / 0.5f;

        t = t * t * (3.f - 2.f * t);

        amount = lerp_float(1.25f, 0.75f, t);
    } else {
        // Stretch: ease-in
        float t = (*phase - 0.5f) / 0.5f;

        t = t * t * t;

        amount = lerp_float(0.75f, 1.25f, t);
    }

    Vec3 scale = squash_stretch(amount);

    local->m[0].p[0] = scale.p[0];
    local->m[1].p[1] = scale.p[1];
    local->m[2].p[2] = scale.p[2];
}