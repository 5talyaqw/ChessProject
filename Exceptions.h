#pragma once
#include <exception>

class NoPieceInSrc : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "No piece in the source position.";
	}

};

class PieceInDst : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "There is already a piece in the destination position.";
	}

};

class SelfCheck : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "The move will result in a check on the current player.";
	}

};

class illegalIndex : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Slot indexes are invalid.";
	}

};

class illegalMovement : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Illegal movement.";
	}

};

class sameDstSrc : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "The destination is the same as the source.";
	}

};