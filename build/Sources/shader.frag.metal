// shader_frag_main

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct shader_frag_main_in
{
    float4 fCol [[user(locn0)]];
};

struct shader_frag_main_out
{
    float4 FragColor [[color(0)]];
};

fragment shader_frag_main_out shader_frag_main(shader_frag_main_in in [[stage_in]])
{
    shader_frag_main_out out = {};
    out.FragColor = in.fCol;
    return out;
}

