#ifndef _openvr_compositor2d_h_
#define _openvr_compositor2d_h_

#include <D3D11_4.h>
#include <d3dcompiler.h>
#include <DXGI1_4.h>
#include <wrl.h>

// #include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"

// extern ID3D11ShaderResourceView *backbufferShResourceView;

namespace vr {
  class PVRCompositor;
}

namespace compositor2d {

void homeRenderLoop();

}

#endif