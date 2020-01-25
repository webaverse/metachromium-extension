#ifndef _openvr_compositor2d_h_
#define _openvr_compositor2d_h_

#include <D3D11_4.h>
#include <d3dcompiler.h>
#include <DXGI1_4.h>
#include <wrl.h>

// #include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"

namespace vr {
  class PVRCompositor;
}

namespace compositor2d {

void initShader(vr::PVRCompositor *pvrcompositor, ID3D11Device5 *device, ID3D11DeviceContext4 *context);
void blendWindow(vr::PVRCompositor *pvrcompositor, ID3D11Device5 *device, ID3D11DeviceContext4 *context, int iEye, ID3D11RenderTargetView *colorRenderTarget, ID3D11RenderTargetView *depthRenderTarget, ID3D11ShaderResourceView *depthIn);

}

#endif