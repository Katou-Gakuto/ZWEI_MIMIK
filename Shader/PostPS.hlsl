#include "PixelShader.h"

cbuffer CONST_BUFFER_LIGHT : register(b3)
{
    float4 lightPos;
};



SamplerState g_SrcSampler       : register( s0 ) ;
Texture2D    g_SrcTexture       : register( t0 ) ;

SamplerState g_BlendSampler     : register( s1 ) ;
Texture2D    g_BlendTexture	    : register( t1 ) ;

struct PS_INPUT
{
    float4 Position : SV_POSITION; // 座標
    float4 DiffuseColor : COLOR0; // ディフューズカラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標０
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標１
};


float4 ps_post(PS_INPUT In) : SV_TARGET0
{
    float4 DestColor;
    
    float2 uv = In.TextureCoord0;
    float2 screen = float2(1920.0f, 1080.0f);  //スクリーンのサイズ

    float2 coord = uv * screen;//画面上の座標に変換する
    
    float2 center = lightPos.xy;//スウィズル
    
    //length →ベクトルの大きさを取得する
    float len = length(center - coord); //中心からの距離

    float light;
        light = 1.2 - (len / 540.0); //中心からの距離で明るさを決める

    
    //0.0～1.0クランプする関数
    light = saturate(light);
    
    
    DestColor = g_SrcTexture.Sample(g_SrcSampler, uv);
    DestColor *= In.DiffuseColor * light;
    

    return DestColor;
}
