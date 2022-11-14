// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Declare our game log categories
DECLARE_LOG_CATEGORY_EXTERN(LogLoner, Log, All);

// Simplify logginer for our games
#define LONER_DISPLAY(msg, ...) UE_LOG(LogLoner, Display, TEXT(msg), __VA_ARGS__) 
#define LONER_WARNING(msg, ...) UE_LOG(LogLoner, Warning, TEXT(msg), __VA_ARGS__) 
#define LONER_ERROR(msg, ...) UE_LOG(LogLoner, Error, TEXT(msg), __VA_ARGS__) 
#define LONER_FATAL(msg, ...) UE_LOG(LogLoner, Fatal, TEXT(msg), __VA_ARGS__) 
