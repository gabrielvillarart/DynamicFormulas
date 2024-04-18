#include "Operation.h"
#include "OperandBuffer.h"

double FOperation::operator()(const FOperandBuffer& Operands) const
{
    return Function(Operands);
}

double FOperations::NoneFunction(const FOperandBuffer& OutOperands)
{ return 0.0; }

double FOperations::LessThanFunction(const FOperandBuffer& OutOperands)
{ 
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A < B ? 1.0 : 0.0;
}

double FOperations::GreaterThanFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A > B ? 1.0 : 0.0;
}

double FOperations::LessEqualThanFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A <= B ? 1.0 : 0.0;
}

double FOperations::GreaterEqualThanFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A >= B ? 1.0 : 0.0;
}

double FOperations::EqualToFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A == B ? 1.0 : 0.0;
}

double FOperations::NotEqualToFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A != B ? 1.0 : 0.0;
}

double FOperations::MaximumFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A > B ? A : B;
}

double FOperations::MinimumFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A < B ? A : B;
}

double FOperations::AverageFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return (A + B) * 0.5;
}

double FOperations::SignFunction(const FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A > 0.0 ? 1.0 : -1.0;
}

double FOperations::NegationFunction(const FOperandBuffer& OutOperands)
{ 
	double A = OutOperands.Pull();

	return -A;
}

double FOperations::AbsoluteFunction(const FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A >= 0.0 ? A : -A;
}

double FOperations::GetNegativeFunction(const FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A >= 0.0 ? -A : A;
}

double FOperations::RoundFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::RoofFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::FloorFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::TruncateFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::AdditionFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A + B;
}

double FOperations::SubtractionFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A - B;
}

double FOperations::MultiplicationFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A * B;
}

double FOperations::DivisionFunction(const FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A / B;
}

double FOperations::ModuloFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::RemainderFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ExponentiationFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SquareFunction(const FOperandBuffer& OutOperands)
{ 
	double A = OutOperands.Pull();

	return A * A;
}

double FOperations::SquareRootFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CubicRootFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SineFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CosineFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::TangentFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SecantFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CosecantFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CotangentFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArcsineFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccosineFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArctangentFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArcsecantFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccosecantFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccotangentFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::LinearInterpolationFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::MapRangeFunction(const FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}