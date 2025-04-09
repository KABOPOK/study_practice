#include <string>
#include"gtest/gtest.h"
#include "boolexpr.h"
#include "algoritms.h"
TEST(create, default_constructor)
{
	BooleanExpression x("~x1      + x6");
	BooleanExpression y("~x1+x6 ");
	BooleanExpression y1("~x1");
	EXPECT_EQ(x, "~x1+x6");
	EXPECT_EQ(y, "~x1+x6");
	EXPECT_EQ(y1, "~x1");
}
TEST(create, special_situation)
{
	BooleanExpression x2("x1+x1+x1");
	EXPECT_EQ(x2.zhegalkin(), "x1");
	BooleanExpression x3("x1+x1+x1+x1");
	EXPECT_EQ(x3.zhegalkin(), "");
}
TEST(operation, default_operation)
{
	BooleanExpression x("x1vx2");
	x.setBoolean("00");
	EXPECT_EQ(0, x.calc());
	x.setBoolean("10");
	EXPECT_EQ(1, x.calc());
	BooleanExpression x1("x1&x2");
	x1.setBoolean("01");
	EXPECT_EQ(0, x1.calc());
	x1.setBoolean("11");
	EXPECT_EQ(1, x1.calc());
	BooleanExpression x2("x1+x2");
	x2.setBoolean("00");
	EXPECT_EQ(0, x2.calc());
	x2.setBoolean("10");
	EXPECT_EQ(1, x2.calc());
	BooleanExpression x3("x1>x2");
	x3.setBoolean("10");
	EXPECT_EQ(0, x3.calc());
	x3.setBoolean("11");
	EXPECT_EQ(1, x3.calc());
	BooleanExpression x4("x1<x2");
	x4.setBoolean("10");
	EXPECT_EQ(1, x4.calc());
	x4.setBoolean("01");
	EXPECT_EQ(0, x4.calc());
	BooleanExpression x5("x1^x2");
	x5.setBoolean("00");
	EXPECT_EQ(1, x5.calc());
	x5.setBoolean("11");
	EXPECT_EQ(0, x5.calc());
	BooleanExpression x6("x1|x2");
	x6.setBoolean("00");
	EXPECT_EQ(1, x6.calc());
	x6.setBoolean("11");
	EXPECT_EQ(0, x6.calc());
	BooleanExpression x7("x1=x2");
	x7.setBoolean("00");
	EXPECT_EQ(1, x7.calc());
	x7.setBoolean("01");
	EXPECT_EQ(0, x7.calc());
}
TEST(operation, dificult_operation) {
	BooleanExpression x("x4vx2&x5+x3|x1=x7");
	EXPECT_EQ(x.zhegalkin(), "x7+x1&x3+x1&x2&x5+x1&x4+x1&x2&x4&x5");
	EXPECT_EQ(x.cnf(), "(x1vx2vx3vx4vx5vx7)&(~x1vx2vx3vx4vx5vx7)&(x1vx2v~x3vx4vx5vx7)&(~x1vx2v~x3vx4vx5v~x7)&(x1vx2vx3vx4v~x5vx7)&(~x1vx2vx3vx4v~x5vx7)&(x1vx2v~x3vx4v~x5vx7)&(~x1vx2v~x3vx4v~x5v~x7)&(x1v~x2vx3vx4vx5vx7)&(~x1v~x2vx3vx4vx5vx7)&(x1v~x2v~x3vx4vx5vx7)&(~x1v~x2v~x3vx4vx5v~x7)&(x1v~x2vx3vx4v~x5vx7)&(~x1v~x2vx3vx4v~x5v~x7)&(x1v~x2v~x3vx4v~x5vx7)&(~x1v~x2v~x3vx4v~x5vx7)&(x1vx2vx3v~x4vx5vx7)&(~x1vx2vx3v~x4vx5v~x7)&(x1vx2v~x3v~x4vx5vx7)&(~x1vx2v~x3v~x4vx5vx7)&(x1vx2vx3v~x4v~x5vx7)&(~x1vx2vx3v~x4v~x5v~x7)&(x1vx2v~x3v~x4v~x5vx7)&(~x1vx2v~x3v~x4v~x5vx7)&(x1v~x2vx3v~x4vx5vx7)&(~x1v~x2vx3v~x4vx5v~x7)&(x1v~x2v~x3v~x4vx5vx7)&(~x1v~x2v~x3v~x4vx5vx7)&(x1v~x2vx3v~x4v~x5vx7)&(~x1v~x2vx3v~x4v~x5v~x7)&(x1v~x2v~x3v~x4v~x5vx7)&(~x1v~x2v~x3v~x4v~x5vx7)");
	EXPECT_EQ(x.dnf(), "(~x1&~x2&~x3&~x4&~x5&x7)v(x1&~x2&~x3&~x4&~x5&x7)v(~x1&~x2&x3&~x4&~x5&x7)v(x1&~x2&x3&~x4&~x5&~x7)v(~x1&~x2&~x3&~x4&x5&x7)v(x1&~x2&~x3&~x4&x5&x7)v(~x1&~x2&x3&~x4&x5&x7)v(x1&~x2&x3&~x4&x5&~x7)v(~x1&x2&~x3&~x4&~x5&x7)v(x1&x2&~x3&~x4&~x5&x7)v(~x1&x2&x3&~x4&~x5&x7)v(x1&x2&x3&~x4&~x5&~x7)v(~x1&x2&~x3&~x4&x5&x7)v(x1&x2&~x3&~x4&x5&~x7)v(~x1&x2&x3&~x4&x5&x7)v(x1&x2&x3&~x4&x5&x7)v(~x1&~x2&~x3&x4&~x5&x7)v(x1&~x2&~x3&x4&~x5&~x7)v(~x1&~x2&x3&x4&~x5&x7)v(x1&~x2&x3&x4&~x5&x7)v(~x1&~x2&~x3&x4&x5&x7)v(x1&~x2&~x3&x4&x5&~x7)v(~x1&~x2&x3&x4&x5&x7)v(x1&~x2&x3&x4&x5&x7)v(~x1&x2&~x3&x4&~x5&x7)v(x1&x2&~x3&x4&~x5&~x7)v(~x1&x2&x3&x4&~x5&x7)v(x1&x2&x3&x4&~x5&x7)v(~x1&x2&~x3&x4&x5&x7)v(x1&x2&~x3&x4&x5&~x7)v(~x1&x2&x3&x4&x5&x7)v(x1&x2&x3&x4&x5&x7)");
}
TEST(operation, big_numbers)
{
	BooleanExpression x("x132vx223");
	EXPECT_EQ(x.cnf(), "(x132vx223)");
	BooleanExpression x1("x132vx223");
	EXPECT_EQ(x1.dnf(), "(~x132&x223)v(x132&~x223)v(x132&x223)");
	BooleanExpression x2("x132vx223");
	EXPECT_EQ(x2.zhegalkin(), "x223+x132+x132&x223");
}
TEST(operation, FullSystemCheck) {
	std::vector<BooleanExpression> box;
	box.push_back("x1vx2&x3");
	box.push_back("x1|x2=x3");
	box.push_back("x1&x2");
	EXPECT_EQ(false, isFullSystem(box));
	std::vector<BooleanExpression> box1;
	box1.push_back("x1vx2&x3");
	box1.push_back("x1|x2=x3");
	box1.push_back("x15|x298");
	EXPECT_EQ(true, isFullSystem(box1));
}
