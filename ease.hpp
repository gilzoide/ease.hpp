#pragma once

#include <cctype>
#include <cmath>
#include <string_view>


namespace ease {

namespace detail {
	/// Return squared value (alternative to `pow(2, ...)` used in AHEasing)
	template<typename T> constexpr T squared(T p) {
		return p * p;
	}

	/// Returns whether 2 string views are equal, ignoring case
	inline bool equals_ignore_case(std::string_view s1, std::string_view s2) {
		if (s1.size() != s2.size()) {
			return false;
		}
		for (int i = 0, count = s1.size(); i < count; i++) {
			if (tolower(s1[i]) != tolower(s2[i])) {
				return false;
			}
		}
		return true;
	}

	/// Returns whether `s` has `prefix`, ignoring case
	inline bool has_prefix_ignore_case(std::string_view s, std::string_view prefix) {
		if (s.size() >= prefix.size()) {
			return equals_ignore_case(s.substr(0, prefix.size()), prefix);
		}
		else {
			return false;
		}
	}

	/// Consumes `prefix` from `s` if the prefix is present, ignoring case.
	/// This also consumes separator characters ` `, `-` and `_` after the prefix, for parsing snake_case and kebab-case strings.
	inline bool consume_prefix_ignore_case(std::string_view& s, std::string_view prefix) {
		if (has_prefix_ignore_case(s, prefix)) {
			s.remove_prefix(prefix.size());
			// Also consume blanks, dashes and underscores
			while (!s.empty() && (s[0] == '-' || s[0] == '_' || s[0] == ' ')) {
				s.remove_prefix(1);
			}
			return true;
		}
		else {
			return false;
		}
	}
}

// Easings based on https://easings.net/
// and this implementation: https://github.com/warrenm/AHEasing/

/// Modeled after the line y = x
template<typename T> constexpr T linear(T p) {
	return p;
}

/// Modeled after the parabola y = x^2
template<typename T> constexpr T in_quadratic(T p) {
	return p * p;
}

/// Modeled after the parabola y = -x^2 + 2x
template<typename T> constexpr T out_quadratic(T p) {
	return -(p * (p - 2));
}

/// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
template<typename T> constexpr T in_out_quadratic(T p) {
	if (p < 0.5)
	{
		return 2 * p * p;
	}
	else
	{
		return (-2 * p * p) + (4 * p) - 1;
	}
}

/// Modeled after the cubic y = x^3
template<typename T> constexpr T in_cubic(T p) {
	return p * p * p;
}

/// Modeled after the cubic y = (x - 1)^3 + 1
template<typename T> constexpr T out_cubic(T p) {
	auto f = (p - 1);
	return f * f * f + 1;
}

/// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
template<typename T> constexpr T in_out_cubic(T p) {
	if (p < 0.5)
	{
		return 4 * p * p * p;
	}
	else
	{
		auto f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

/// Modeled after the quartic x^4
template<typename T> constexpr T in_quartic(T p) {
	return p * p * p * p;
}

/// Modeled after the quartic y = 1 - (x - 1)^4
template<typename T> constexpr T out_quartic(T p) {
	auto f = (p - 1);
	return f * f * f * (1 - p) + 1;
}

/// Modeled after the piecewise quartic
// y = (1/2)((2x)^4)        ; [0, 0.5)
// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
template<typename T> constexpr T in_out_quartic(T p) {
	if (p < 0.5)
	{
		return 8 * p * p * p * p;
	}
	else
	{
		auto f = (p - 1);
		return -8 * f * f * f * f + 1;
	}
}

/// Modeled after the quintic y = x^5
template<typename T> constexpr T in_quintic(T p) {
	return p * p * p * p * p;
}

/// Modeled after the quintic y = (x - 1)^5 + 1
template<typename T> constexpr T out_quintic(T p) {
	auto f = (p - 1);
	return f * f * f * f * f + 1;
}

/// Modeled after the piecewise quintic
// y = (1/2)((2x)^5)       ; [0, 0.5)
// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
template<typename T> constexpr T in_out_quintic(T p) {
	if (p < 0.5)
	{
		return 16 * p * p * p * p * p;
	}
	else
	{
		auto f = ((2 * p) - 2);
		return  0.5 * f * f * f * f * f + 1;
	}
}

/// Modeled after quarter-cycle of sine wave
template<typename T> T in_sine(T p) {
	return sin((p - 1) * M_PI_2) + 1;
}

/// Modeled after quarter-cycle of sine wave (different phase)
template<typename T> T out_sine(T p) {
	return sin(p * M_PI_2);
}

/// Modeled after half sine wave
template<typename T> T in_out_sine(T p) {
	return 0.5 * (1 - cos(p * M_PI));
}

/// Modeled after shifted quadrant IV of unit circle
template<typename T> T in_circular(T p) {
	return 1 - sqrt(1 - (p * p));
}

/// Modeled after shifted quadrant II of unit circle
template<typename T> T out_circular(T p) {
	return sqrt((2 - p) * p);
}

/// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
template<typename T> T in_out_circular(T p) {
	if (p < 0.5)
	{
		return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
	}
	else
	{
		return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
	}
}

/// Modeled after the exponential function y = 2^(10(x - 1))
template<typename T> constexpr T in_exponential(T p) {
	return (p == 0.0) ? p : detail::squared(10 * (p - 1));
}

/// Modeled after the exponential function y = -2^(-10x) + 1
template<typename T> constexpr T out_exponential(T p) {
	return (p == 1.0) ? p : 1 - detail::squared(-10 * p);
}

/// Modeled after the piecewise exponential
// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
template<typename T> constexpr T in_out_exponential(T p) {
	if (p == 0.0 || p == 1.0) return p;

	if (p < 0.5)
	{
		return 0.5 * detail::squared((20 * p) - 10);
	}
	else
	{
		return -0.5 * detail::squared((-20 * p) + 10) + 1;
	}
}

/// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
template<typename T> T in_elastic(T p) {
	return sin(13 * M_PI_2 * p) * detail::squared(10 * (p - 1));
}

/// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
template<typename T> T out_elastic(T p) {
	return sin(-13 * M_PI_2 * (p + 1)) * detail::squared(-10 * p) + 1;
}

/// Modeled after the piecewise exponentially-damped sine wave:
// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
template<typename T> T in_out_elastic(T p) {
	if (p < 0.5)
	{
		return 0.5 * sin(13 * M_PI_2 * (2 * p)) * detail::squared(10 * ((2 * p) - 1));
	}
	else
	{
		return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * detail::squared(-10 * (2 * p - 1)) + 2);
	}
}

/// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
template<typename T> T in_back(T p) {
	return p * p * p - p * sin(p * M_PI);
}

/// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
template<typename T> T out_back(T p) {
	auto f = (1 - p);
	return 1 - (f * f * f - f * sin(f * M_PI));
}

/// Modeled after the piecewise overshooting cubic function:
// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
template<typename T> T in_out_back(T p) {
	if (p < 0.5)
	{
		auto f = 2 * p;
		return 0.5 * (f * f * f - f * sin(f * M_PI));
	}
	else
	{
		auto f = (1 - (2*p - 1));
		return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
	}
}

template<typename T> constexpr T out_bounce(T p) {
	if (p < 4/11.0)
	{
		return (121 * p * p)/16.0;
	}
	else if (p < 8/11.0)
	{
		return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
	}
	else if (p < 9/10.0)
	{
		return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
	}
	else
	{
		return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
	}
}

template<typename T> constexpr T in_bounce(T p) {
	return 1 - out_bounce(1 - p);
}

template<typename T> constexpr T in_out_bounce(T p) {
	if (p < 0.5)
	{
		return 0.5 * in_bounce(p*2);
	}
	else
	{
		return 0.5 * out_bounce(p * 2 - 1) + 0.5;
	}
}

/// Ease function enumeration
enum function {
	LINEAR,

	IN_QUADRATIC,
	OUT_QUADRATIC,
	IN_OUT_QUADRATIC,

	IN_CUBIC,
	OUT_CUBIC,
	IN_OUT_CUBIC,

	IN_QUARTIC,
	OUT_QUARTIC,
	IN_OUT_QUARTIC,

	IN_QUINTIC,
	OUT_QUINTIC,
	IN_OUT_QUINTIC,

	IN_SINE,
	OUT_SINE,
	IN_OUT_SINE,

	IN_CIRCULAR,
	OUT_CIRCULAR,
	IN_OUT_CIRCULAR,

	IN_EXPONENTIAL,
	OUT_EXPONENTIAL,
	IN_OUT_EXPONENTIAL,

	IN_ELASTIC,
	OUT_ELASTIC,
	IN_OUT_ELASTIC,

	IN_BACK,
	OUT_BACK,
	IN_OUT_BACK,

	IN_BOUNCE,
	OUT_BOUNCE,
	IN_OUT_BOUNCE,
};

/// Function pointer type for ease functions
template<typename T> using function_ptr = T (*)(T);

/// Get the function pointer for an ease function using an enum.
/// Returns `nullptr` for unknown enum values.
template<typename T> constexpr function_ptr<T> get(function f) {
	switch (f) {
		case LINEAR: return linear;
		case IN_QUADRATIC: return in_quadratic;
		case OUT_QUADRATIC: return out_quadratic;
		case IN_OUT_QUADRATIC: return in_out_quadratic;
		case IN_CUBIC: return in_cubic;
		case OUT_CUBIC: return out_cubic;
		case IN_OUT_CUBIC: return in_out_cubic;
		case IN_QUARTIC: return in_quartic;
		case OUT_QUARTIC: return out_quartic;
		case IN_OUT_QUARTIC: return in_out_quartic;
		case IN_QUINTIC: return in_quintic;
		case OUT_QUINTIC: return out_quintic;
		case IN_OUT_QUINTIC: return in_out_quintic;
		case IN_SINE: return in_sine;
		case OUT_SINE: return out_sine;
		case IN_OUT_SINE: return in_out_sine;
		case IN_CIRCULAR: return in_circular;
		case OUT_CIRCULAR: return out_circular;
		case IN_OUT_CIRCULAR: return in_out_circular;
		case IN_EXPONENTIAL: return in_exponential;
		case OUT_EXPONENTIAL: return out_exponential;
		case IN_OUT_EXPONENTIAL: return in_out_exponential;
		case IN_ELASTIC: return in_elastic;
		case OUT_ELASTIC: return out_elastic;
		case IN_OUT_ELASTIC: return in_out_elastic;
		case IN_BACK: return in_back;
		case OUT_BACK: return out_back;
		case IN_OUT_BACK: return in_out_back;
		case IN_BOUNCE: return in_bounce;
		case OUT_BOUNCE: return out_bounce;
		case IN_OUT_BOUNCE: return in_out_bounce;
		default: return nullptr;
	}
}

/// Get the function pointer for an ease function using its name.
/// Supports any casing, as well as whitespace, `_` and `-`, so that "IN_CUBIC" is the same as "InCubic" or "in cubic".
/// Returns `nullptr` for unknown names.
template<typename T> function_ptr<T> get(std::string_view name) {
	if (detail::equals_ignore_case(name, "linear")) {
		return linear;
	}
	else if (detail::consume_prefix_ignore_case(name, "in")) {
		if (detail::consume_prefix_ignore_case(name, "out")) {
			if (detail::equals_ignore_case(name, "quadratic")) return in_out_quadratic;
			else if (detail::equals_ignore_case(name, "cubic")) return in_out_cubic;
			else if (detail::equals_ignore_case(name, "quartic")) return in_out_quartic;
			else if (detail::equals_ignore_case(name, "quintic")) return in_out_quintic;
			else if (detail::equals_ignore_case(name, "sine")) return in_out_sine;
			else if (detail::equals_ignore_case(name, "circular")) return in_out_circular;
			else if (detail::equals_ignore_case(name, "exponential")) return in_out_exponential;
			else if (detail::equals_ignore_case(name, "elastic")) return in_out_elastic;
			else if (detail::equals_ignore_case(name, "back")) return in_out_back;
			else if (detail::equals_ignore_case(name, "bounce")) return in_out_bounce;
		}
		else {
			if (detail::equals_ignore_case(name, "quadratic")) return in_quadratic;
			else if (detail::equals_ignore_case(name, "cubic")) return in_cubic;
			else if (detail::equals_ignore_case(name, "quartic")) return in_quartic;
			else if (detail::equals_ignore_case(name, "quintic")) return in_quintic;
			else if (detail::equals_ignore_case(name, "sine")) return in_sine;
			else if (detail::equals_ignore_case(name, "circular")) return in_circular;
			else if (detail::equals_ignore_case(name, "exponential")) return in_exponential;
			else if (detail::equals_ignore_case(name, "elastic")) return in_elastic;
			else if (detail::equals_ignore_case(name, "back")) return in_back;
			else if (detail::equals_ignore_case(name, "bounce")) return in_bounce;
		}
	}
	else if (detail::consume_prefix_ignore_case(name, "out")) {
		if (detail::equals_ignore_case(name, "quadratic")) return out_quadratic;
		else if (detail::equals_ignore_case(name, "cubic")) return out_cubic;
		else if (detail::equals_ignore_case(name, "quartic")) return out_quartic;
		else if (detail::equals_ignore_case(name, "quintic")) return out_quintic;
		else if (detail::equals_ignore_case(name, "sine")) return out_sine;
		else if (detail::equals_ignore_case(name, "circular")) return out_circular;
		else if (detail::equals_ignore_case(name, "exponential")) return out_exponential;
		else if (detail::equals_ignore_case(name, "elastic")) return out_elastic;
		else if (detail::equals_ignore_case(name, "back")) return out_back;
		else if (detail::equals_ignore_case(name, "bounce")) return out_bounce;
	}
	return nullptr;
}

}
