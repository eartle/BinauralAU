//
//
//

#ifndef __HRTF_H__
#define __HRTF_H__

#define LENGTH 128

#define PREC_ELEV_40 29
#define PREC_ELEV_30 31
#define PREC_ELEV_20 37
#define PREC_ELEV_10 37
#define PREC_ELEV0 37
#define PREC_ELEV10 37
#define PREC_ELEV20 37
#define PREC_ELEV30 31
#define PREC_ELEV40 29
#define PREC_ELEV50 23
#define PREC_ELEV60 19
#define PREC_ELEV70 13
#define PREC_ELEV80 7
#define PREC_ELEV90 1

const float ImpResElev_40[2][PREC_ELEV_40][LENGTH] =
	{
#include "hrtfs/hrtf_elev-40.h"
	};

const float ImpResElev_30[2][PREC_ELEV_30][LENGTH] =
	{
#include "hrtfs/hrtf_elev-30.h"
	};

const float ImpResElev_20[2][PREC_ELEV_20][LENGTH] =
	{
#include "hrtfs/hrtf_elev-20.h"
	};

const float ImpResElev_10[2][PREC_ELEV_10][LENGTH] =
	{
#include "hrtfs/hrtf_elev-10.h"
	};

const float ImpResElev0[2][PREC_ELEV0][LENGTH] =
	{
#include "hrtfs/hrtf_elev0.h"
	};

const float ImpResElev10[2][PREC_ELEV10][LENGTH] =
	{
#include "hrtfs/hrtf_elev10.h"
	};

const float ImpResElev20[2][PREC_ELEV20][LENGTH] =
	{
#include "hrtfs/hrtf_elev20.h"
	};

const float ImpResElev30[2][PREC_ELEV30][LENGTH] =
	{
#include "hrtfs/hrtf_elev30.h"
	};

const float ImpResElev40[2][PREC_ELEV40][LENGTH] =
	{
#include "hrtfs/hrtf_elev40.h"
	};

const float ImpResElev50[2][PREC_ELEV50][LENGTH] =
	{
#include "hrtfs/hrtf_elev50.h"
	};

const float ImpResElev60[2][PREC_ELEV60][LENGTH] =
	{
#include "hrtfs/hrtf_elev60.h"
	};

const float ImpResElev70[2][PREC_ELEV70][LENGTH] =
	{
#include "hrtfs/hrtf_elev70.h"
	};

const float ImpResElev80[2][PREC_ELEV80][LENGTH] =
	{
#include "hrtfs/hrtf_elev80.h"
	};

const float ImpResElev90[2][PREC_ELEV90][LENGTH] =
	{
#include "hrtfs/hrtf_elev90.h"
	};

#endif // __HRTF_H__