/* Copyright (c) 2020 Gabriel Borges. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#define GL_SILENCE_DEPRECATION 1

#include <napi.h>
#include <node.h>

#include "gl/context.h"


static Napi::Object Init(Napi::Env env, Napi::Object exports) {

  Context::Init(env, exports);

  return exports;
}

NODE_API_MODULE(opengl_context, Init)

