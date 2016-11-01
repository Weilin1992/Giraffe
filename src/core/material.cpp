/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:38:43
**/

#include "../utility/sampler.hpp"

#include "material.hpp"

namespace Giraffe {

Color Material::brdf(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
{
	switch (type_) {
		case kDiffuse:
			return sampleDiffuse(out, in, normal, pdf);
		case kReflect:
			return sampleReflect(out, in, normal, pdf);
		case kRefract:
			return sampleRefract(out, in, normal, pdf);
		case kPhong:
			return samplePhong(out, in, normal, pdf);
		case kGlossy:
			return sampleGlossy(out, in, normal, pdf);
		case kRetro:
			return sampleRetro(out, in, normal, pdf);
		case kHalton:
			return sampleHalton(out, in, normal, pdf);
	}
	assert(0);
}

Color Material::evaluate(const Vector3d &out, const Vector3d &in, const Vector3d &normal)
{
	switch (type_) {
		default:
			return evaluateDiffuse(out, in, normal);
		case kPhong:
			return evaluatePhong(out, in, normal);
	}
	assert(0);
}

Color Material::sampleDiffuse(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{

	in = sampleCosHemisphere(normal);

	return color_;
}

Color Material::sampleReflect(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = normalize(out - (2 * dot(out, normal)) * normal);

	return color_;
}

Color Material::sampleRefract(const Vector3d &out, Vector3d &in, const Vector3d &Normal,
	double &pdf)
{
	return Vector3d();
}

Color Material::samplePhong(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosHemisphere(normal);
	return color_;
}

Color Material::sampleGlossy(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosSphere(normalize(out - (2 * dot(out, normal)) * normal), sin_, cos_);

	return color_;
}

Color Material::sampleRetro(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosSphere(-out, sin_, cos_);

	return color_;
}

Color Material::sampleHalton(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	return Vector3d();
}

Color Material::evaluateDiffuse(const Vector3d &out, const Vector3d &in, const Vector3d &normal)
{
	return color_ * dot(normal, in);
}

Color Material::evaluatePhong(const Vector3d &out, const Vector3d &in, const Vector3d &normal)
{
	Vector3d mid(normalize(in - out));
	// return mult(intensity, color_ * dot(normal, in)) + intensity * std::pow(dot(normal, mid), 2);
	return color_ * (dot(normal, in) + std::pow(dot(normal, mid), pow_));
}

} // namespace Giraffe