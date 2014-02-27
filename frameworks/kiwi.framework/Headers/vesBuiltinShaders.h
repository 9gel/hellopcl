#ifndef __vesBuiltinShaders_h

/// vesBuiltinShaders provides accessors to builtin glsl shader program source code.
/// \ingroup shaders
class vesBuiltinShaders {
public:
  /// Get the source to the vesBackgroundTexture_frag.glsl shader program
  static char* vesBackgroundTexture_frag();

  /// Get the source to the vesBackgroundTexture_vert.glsl shader program
  static char* vesBackgroundTexture_vert();

  /// Get the source to the vesBlinnPhong_frag.glsl shader program
  static char* vesBlinnPhong_frag();

  /// Get the source to the vesBlinnPhong_vert.glsl shader program
  static char* vesBlinnPhong_vert();

  /// Get the source to the vesCap_frag.glsl shader program
  static char* vesCap_frag();

  /// Get the source to the vesCap_vert.glsl shader program
  static char* vesCap_vert();

  /// Get the source to the vesClipPlane_frag.glsl shader program
  static char* vesClipPlane_frag();

  /// Get the source to the vesClipPlane_vert.glsl shader program
  static char* vesClipPlane_vert();

  /// Get the source to the vesGouraudTexture_frag.glsl shader program
  static char* vesGouraudTexture_frag();

  /// Get the source to the vesGouraudTexture_vert.glsl shader program
  static char* vesGouraudTexture_vert();

  /// Get the source to the vesShader_frag.glsl shader program
  static char* vesShader_frag();

  /// Get the source to the vesShader_vert.glsl shader program
  static char* vesShader_vert();

  /// Get the source to the vesTestTexture_frag.glsl shader program
  static char* vesTestTexture_frag();

  /// Get the source to the vesTestTexture_vert.glsl shader program
  static char* vesTestTexture_vert();

  /// Get the source to the vesToonShader_frag.glsl shader program
  static char* vesToonShader_frag();

  /// Get the source to the vesToonShader_vert.glsl shader program
  static char* vesToonShader_vert();

  /// Get the source to the vesWireframeShader_frag.glsl shader program
  static char* vesWireframeShader_frag();

  /// Get the source to the vesWireframeShader_vert.glsl shader program
  static char* vesWireframeShader_vert();

};
#endif
