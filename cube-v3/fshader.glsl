#version 330 core

// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

uniform sampler2D cube_texture;

in vec2 v_texcoord;

layout(location = 0) out vec4 fragColor;

//! [0]
void main()
{
    // Set fragment color from texture
    fragColor = texture(cube_texture, v_texcoord);
}
//! [0]

