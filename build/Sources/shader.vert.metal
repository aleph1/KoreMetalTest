// shader_vert_main

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct shader_vert_main_in
{
    float3 pos [[attribute(0)]];
    float4 col [[attribute(1)]];
};

struct shader_vert_main_out
{
    float4 fCol [[user(locn0)]];
    float4 gl_Position [[position]];
};

struct shader_vert_main_uniforms
{
    float4x4 projectionMatrix;
};

vertex shader_vert_main_out shader_vert_main(shader_vert_main_in in [[stage_in]], constant shader_vert_main_uniforms& uniforms [[buffer(1)]], uint gl_VertexID [[vertex_id]], uint gl_InstanceID [[instance_id]])
{
    shader_vert_main_out out = {};
    out.gl_Position = uniforms.projectionMatrix * float4(in.pos, 1.0);
    out.fCol = in.col;
    out.gl_Position.z = (out.gl_Position.z + out.gl_Position.w) * 0.5;       // Adjust clip-space for Metal
    return out;
}

