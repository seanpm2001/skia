/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "GrCommandBuilder.h"

#include "GrInOrderCommandBuilder.h"
#include "GrReorderCommandBuilder.h"

GrCommandBuilder* GrCommandBuilder::Create(GrGpu* gpu, bool reorder) {
    if (reorder) {
        return SkNEW(GrReorderCommandBuilder);
    } else {
        return SkNEW(GrInOrderCommandBuilder);
    }
}

GrTargetCommands::Cmd* GrCommandBuilder::recordClearStencilClip(const SkIRect& rect,
                                                                bool insideClip,
                                                                GrRenderTarget* renderTarget) {
    SkASSERT(renderTarget);

    ClearStencilClip* clr = GrNEW_APPEND_TO_RECORDER(*this->cmdBuffer(),
                                                     ClearStencilClip,
                                                     (renderTarget));
    clr->fRect = rect;
    clr->fInsideClip = insideClip;
    GrBATCH_INFO("Recording clear stencil clip %d\n", clr->uniqueID());
    return clr;
}

GrTargetCommands::Cmd* GrCommandBuilder::recordCopySurface(GrSurface* dst,
                                                           GrSurface* src,
                                                           const SkIRect& srcRect,
                                                           const SkIPoint& dstPoint) {
    CopySurface* cs = GrNEW_APPEND_TO_RECORDER(*this->cmdBuffer(), CopySurface, (dst, src));
    cs->fSrcRect = srcRect;
    cs->fDstPoint = dstPoint;
    GrBATCH_INFO("Recording copysurface %d\n", cs->uniqueID());
    return cs;
}
