import QtQuick 2.10

ShaderEffect {
    id: circleProgressShader

    property real progress
    property real reachedProgressOpacity
    property real unreachedProgressOpacity

    fragmentShader: "
        varying highp vec2 qt_TexCoord0;
        uniform lowp float qt_Opacity;

        uniform sampler2D source;
        uniform lowp float progress;
        uniform lowp float reachedProgressOpacity;
        uniform lowp float unreachedProgressOpacity;

        void main() {
            // Convert texture coordinates from range [0,1] to [-1,1]
            lowp vec2 coord2 = qt_TexCoord0 * 2.0 - 1.0;

            // Calculate angle using atan function (it will be in range [-PI,PI])
            // and convert it to range [0,1] (divide by PI*2 and add 0.5)
            lowp float angle = atan(-coord2.x, coord2.y) / 6.283185307179586 + 0.5;
            lowp float opacity = angle <= progress ? reachedProgressOpacity : unreachedProgressOpacity;

            gl_FragColor = texture2D(source, qt_TexCoord0) * qt_Opacity * opacity;
        }
    "
}
