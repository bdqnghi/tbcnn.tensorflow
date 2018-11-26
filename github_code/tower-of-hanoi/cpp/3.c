/**
 * \file    tower_of_hanoi_console.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "tower_of_hanoi_console.h"
#include "hanoi_puzzle_algorithm.h"

TowerOfHanoiConsole :: TowerOfHanoiConsole(int argc, char ** argv) :
	_rods(3),
	_visual(3),
	_retval(0)
{
	if (argc < 2) {
		std :: cerr << "usage: " << *argv << ": <disk quantity>\n";
		_retval = 1;
	}

	QString a_str(argv[1]);
	bool ok = false;
	_diskQuantity = a_str.toInt(&ok);
	if (!ok || _diskQuantity <= 0 || _diskQuantity > 10) {
		std :: cerr << "invalid disk quantity [1 .. 10]\n";
		_retval = 1;
	}
}


TowerOfHanoiConsole :: ~TowerOfHanoiConsole()
{

}

int TowerOfHanoiConsole :: exec()
{
	if (_retval == 1)
		return _retval;

	_rods.reset(_diskQuantity);

	_visual.createInterface(_diskQuantity);

	HanoiPuzzleAlgorithm algo(_diskQuantity);

	std :: size_t step = 0;

	std :: cout << step++ << ".\n\n";
	_visual.show(_rods);

	algo.start([&](int src, int dst, int diskId, void * arg) {
		Q_UNUSED(diskId);
		Q_UNUSED(arg);
		std :: cout << step++ << ".\n\n";
		bool ok = _rods.moveDisk(src, dst);
		Q_ASSERT(ok);
		_visual.show(_rods);
	},
	nullptr);

	Q_ASSERT(_rods.isFinished());

	return 0;
}
