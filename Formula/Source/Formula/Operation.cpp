#include "Operation.h"
#include "OperandBuffer.h"

double FOperation::operator()(FOperandBuffer& Operands) const
{
    return Function(Operands);
}

double FOperations::NoneFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed. }

double FOperations::LessThanFunction(FOperandBuffer& OutOperands)
{ 
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A < B ? 1.0 : 0.0;
}

double FOperations::GreaterThanFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A > B ? 1.0 : 0.0;
}

double FOperations::LessEqualThanFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A <= B ? 1.0 : 0.0;
}

double FOperations::GreaterEqualThanFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A >= B ? 1.0 : 0.0;
}

double FOperations::EqualToFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A == B ? 1.0 : 0.0;
}

double FOperations::NotEqualToFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A != B ? 1.0 : 0.0;
}

double FOperations::MaximumFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A > B ? A : B;
}

double FOperations::MinimumFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A < B ? A : B;
}

double FOperations::AverageFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return (A + B) * 0.5;
}

double FOperations::SignFunction(FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A > 0.0 ? 1.0 : -1.0;
}

double FOperations::NegationFunction(FOperandBuffer& OutOperands)
{ 
	double A = OutOperands.Pull();

	return -A;
}

double FOperations::AbsoluteFunction(FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A >= 0.0 ? A : -A;
}

double FOperations::GetNegativeFunction(FOperandBuffer& OutOperands)
{
	double A = OutOperands.Pull();

	return A >= 0.0 ? -A : A;
}

double FOperations::RoundFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::RoofFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::FloorFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::TruncateFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::AdditionFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A + B;
}

double FOperations::SubtractionFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A - B;
}

double FOperations::MultiplicationFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A * B;
}

double FOperations::DivisionFunction(FOperandBuffer& OutOperands)
{
	double B = OutOperands.Pull();
	double A = OutOperands.Pull();

	return A / B;
}

double FOperations::ModuloFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::RemainderFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ExponentiationFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SquareFunction(FOperandBuffer& OutOperands)
{ 
	double A = OutOperands.Pull();

	return A * A;
}

double FOperations::SquareRootFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CubicRootFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SineFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CosineFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::TangentFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::SecantFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CosecantFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::CotangentFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArcsineFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccosineFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArctangentFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArcsecantFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccosecantFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::ArccotangentFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::LinearInterpolationFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}

double FOperations::MapRangeFunction(FOperandBuffer& OutOperands)
{ return 0.0; // To be developed.
}