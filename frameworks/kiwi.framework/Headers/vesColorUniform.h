#ifndef VESCOLORUNIFORM_H
#define VESCOLORUNIFORM_H

#include "vesUniform.h"

// VES includes
#include "vesRenderState.h"
#include "vesSetGet.h"

// C++ includes
#include <string>

class vesColorUniform : public vesUniform
{
public:
  vesColorUniform(const std::string &name="colorUniform") :
    vesUniform(name, vesVector4f())
  {
  }


  virtual void update(const vesRenderState   &renderState,
                      const vesShaderProgram &program)
  {
    vesNotUsed(renderState);
    vesNotUsed(program);
  }
};

#endif // VESCOLORUNIFORM_H
