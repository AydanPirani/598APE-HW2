#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <node.h>
#include <array>
#include <functional>
#include <iostream>
#include <cassert>

namespace genetic {
namespace detail {

static constexpr float MIN_VAL = 0.001f;

inline bool is_terminal(node::type t) {
  return t == node::type::variable || t == node::type::constant;
}

inline bool is_nonterminal(node::type t) { return !is_terminal(t); }

inline int arity(node::type t) {
  if (node::type::unary_begin <= t && t <= node::type::unary_end) {
    return 1;
  }
  if (node::type::binary_begin <= t && t <= node::type::binary_end) {
    return 2;
  }
  return 0;
}


// binary operators array
// add
// atan2
// div
// fdim
// max
// min
// mul
// pow
// sub

// subtraction operators array
// abs
// acos
// acosh
// asin
// asinh
// atan
// atanh
// cbrt
// cos
// cosh
// cube
// exp
// inv
// log
// neg
// rcbrt
// rsqrt
// sin
// sinh
// sq
// sqrt
// tan
// tanh
static std::array<std::function<float(const float* in)>, 35> precomputed_funcs = {
  // variable
  [](const float* in) { return 0; }, 

  // constant
  [](const float* in) { return 0; },

  // functions_begin, binary_begin, add
  [](const float* in) { return in[0] + in[1]; },
  
  // atan2
  [](const float* in) { return atan2f(in[0], in[1]); },

  // div
  [](const float* in) { return fabsf(in[1]) < MIN_VAL ? 1.0f : (in[0] / in[1]); },

  // fdim
  [](const float* in) { return fdimf(in[0], in[1]); },

  // max
  [](const float* in) { return fmaxf(in[0], in[1]); },

  // min
  [](const float* in) { return fminf(in[0], in[1]); },

  // mul
  [](const float* in) { return in[0] * in[1]; },

  // pow
  [](const float* in) { return powf(in[0], in[1]); },

  // sub, binary_end
  [](const float* in) { return in[0] - in[1]; },

  // unary_begin, abs
  [](const float* in) {return fabsf(in[0]); },
  // fabsf(in[0])

  // acos
  [](const float* in) { return acosf(in[0]); },

  // acosh
  [](const float* in) { return acoshf(in[0]); },

  // asin
  [](const float* in) { return asinf(in[0]); },
  
  // asinh
  [](const float* in) { return asinhf(in[0]); },

  // atan
  [](const float* in) { return atanf(in[0]); },

  // atanh
  [](const float* in) { return atanhf(in[0]); },
  
  // cbrt
  [](const float* in) { return cbrtf(in[0]); },

  // cos
  [](const float* in) { return cosf(in[0]); },

  // cosh
  [](const float* in) { return coshf(in[0]); },
  
  // cube
  [](const float* in) { return in[0] * in[0] * in[0]; },
  
  // exp
  [](const float* in) { return expf(in[0]); },
  
  // inv
  [](const float* in) { return fabs(in[0]) < MIN_VAL ? 0.f : 1.f / in[0]; },
  
  // log
  [](const float* in) { return fabs(in[0]) < MIN_VAL ? 0.f : logf(fabs(in[0])); },

  // neg
  [](const float* in) { return -in[0]; },

  // rcbrt
  [](const float* in) {return static_cast<float>(1.0) / cbrtf(in[0]); },

  // rsqrt
  [](const float* in) { return static_cast<float>(1.0) / sqrtf(fabsf(in[0])); },
  
  // sin
  [](const float* in) { return sinf(in[0]); },
  
  // sinh
  [](const float* in) { return sinhf(in[0]); },
  
  // sq
  [](const float* in) { return in[0] * in[0]; },
  
  // sqrt
  [](const float* in) { return sqrtf(fabsf(in[0])); },
  
  // tan
  [](const float* in) { return tanf(in[0]); },
  
  // unary_end, tanh, functions_end
  [](const float* in) { return tanhf(in[0]); },
};


// `data` assumed to be stored in col-major format
inline float evaluate_node(const node &n, const float *data, const uint64_t stride,
                    const uint64_t idx, const float *in) {
  if (n.t == node::type::constant) {
    return n.u.val;
  } else if (n.t == node::type::variable) {
    return data[(stride * n.u.fid) + idx];
  } else {
    float rv = precomputed_funcs[(int) n.t](in);
    return rv;
  }
}

} // namespace detail
} // namespace genetic
