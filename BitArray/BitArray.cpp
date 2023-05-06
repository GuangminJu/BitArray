// Type your code here, or load an example.

#include <iostream>
#include <vector>

using namespace std;

class FBitReference
{
public:

	FBitReference(unsigned& InData, unsigned InMask)
		: Data(InData)
		, Mask(InMask)
	{}

	operator bool() const
	{
		return (Data & Mask) != 0;
	}
	void operator=(const bool NewValue)
	{
		if (NewValue)
		{
			Data |= Mask;
		}
		else
		{
			Data &= ~Mask;
		}
	}
	void operator|=(const bool NewValue)
	{
		if (NewValue)
		{
			Data |= Mask;
		}
	}
	void operator&=(const bool NewValue)
	{
		if (!NewValue)
		{
			Data &= ~Mask;
		}
	}

	FBitReference& operator=(const FBitReference& Copy)
	{
		*this = (bool)Copy;
		return *this;
	}

private:
	unsigned& Data;
	unsigned Mask;
};

class TBitArray
{
public:
	TBitArray(unsigned InSize) : Data(nullptr), SizeMax(InSize)
	{
		Data = malloc(SizeMax);
		Init(false);
	}
	~TBitArray()
	{
		free(Data);
	}

	void* GetData()
	{
		return Data;
	}

	void Init(bool InV)
	{
		for (unsigned i = 0; i < SizeMax; i++)
		{
			(*this)[i] = InV;
		}
	}

	const FBitReference operator[](const unsigned Idx) const
	{
		return (*this)[Idx];
	}

	FBitReference operator[](const unsigned Idx)
	{
		return FBitReference(((unsigned*)GetData())[Idx / 32], 1 << (Idx & 32 - 1));
	}

private:
	void* Data;
	unsigned SizeMax;
};

int main(int ac, char** av)
{
	cout << "Input Size Max:";

	unsigned Size = 0;
	cin >> Size;

	TBitArray TempArray(Size);

	unsigned Idx = 0;
	bool Value = false;

	for (;;)
	{
		for (unsigned i = 0; i < Size; i++)
		{
			cout << TempArray[i];
		}

		cout << endl;

		cout << "Input Idx:";
		cin >> Idx;
		cout << "Input Value:";
		cin >> Value;

		TempArray[Idx] = Value;
	}

	return 0;
}