// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISingleton.h"
/**
 * 
 */
template<class T>
class WARRIOR_API Singleton
{
private :
	static T* _instance;
	Singleton();
public:
	static inline T* GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new T();
			ISingleton* i = static_cast<ISingleton*>(_instance);
			i->OnNew();
		}		
		return _instance;
	}
	static void Dispose()
	{
		if (_instance == NULL)
			return;
		delete _instance;
		_instance = NULL;
	}
	~Singleton();
};
