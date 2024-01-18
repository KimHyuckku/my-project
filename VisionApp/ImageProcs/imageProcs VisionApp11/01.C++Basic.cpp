#include <iostream>
#include <vector>
class Shape
{
public:
	Shape()
		:a(0)//member initialize
		, b(10)
		, pA(nullptr)
	{
		//copy operator
		a = 1;
		b = 2;
		std::cout << "Ctor" << std::endl;
	}
	~Shape();
private:
	int a, b;
	int* pA;
};
//#define CIRCLE 100
//#define RECTANGE 101
const size_t _CIRCLE = 100;

enum EShape {
	eCircle=0,
	eRectangle,
	eTriangle,
	ePoly,
	eShapeMax
};

int main()
{
	int a = 1;
	//int ctor->instance->|a|->operator '=' -> 1
	int b(20);
	//int ctor->instance + 2 (initilized)
	int c = a + b;
	std::cout << c << "\t=\t" << a << "\t+\t" << b << std::endl;

	int* pA = nullptr;
	std::cout << "size of pointer pA = " << sizeof(pA) << std::endl;

	EShape _eShape = EShape::eCircle;
	//resource create
	int* pShape = new int[EShape::eShapeMax];

	//init and management
	memset((void*)pShape, 0,sizeof(int)* EShape::eShapeMax);
	
	//destroy
	if (pShape != nullptr)
	{
		delete[] pShape;
		pShape = nullptr;
	}
	

	std::vector<int> vShape(EShape::eShapeMax, 0);
	vShape[0] = 1;
	vShape[1] = 2;
	vShape[2] = 3;
	vShape[3] = 4;
	
	
	return 1;
}
