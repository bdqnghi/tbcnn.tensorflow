#include "HanoiTower.hpp"


using namespace std;
using namespace clever;






HanoiTower::HanoiTower(HanoiTowerData const &data):
	d_(data), interrupt_(false)
{
	pauselock_ = unique_lock<mutex>(pausemutex_, defer_lock);
	return;
}

HanoiTower::~HanoiTower()
{
	free_();
	return;
}






HanoiTower &HanoiTower::run(int from, int to)
{
#ifdef DEBUG
	if(future_.valid())
		throw "run when future is valid";
#endif
	future_ = async(
		launch::async,
		&HanoiTower::work_implement_,
		this, &d_, from, to
	);
	return *this;
}

bool HanoiTower::isRun() const
{
	return future_.valid();
}


HanoiTower &HanoiTower::pause(bool enable)
{
	if(enable)
	{
		if(!pauselock_)
			pauselock_.lock();
	}
	else
	{
		if(pauselock_)
			pauselock_.unlock();
	}
	return *this;
}

bool HanoiTower::pause() const
{
	return pauselock_.owns_lock();
}


HanoiTower &HanoiTower::wait()
{
	if(pauselock_)
		throw "wait, but pause is enable";

	if(future_.valid())
		future_.get();

	interrupt_.store(false);
	return *this;
}

HanoiTower &HanoiTower::interrupt()
{
	if(future_.valid());
	interrupt_.store(true);
	pause(false);
	return *this;
}

HanoiTower &HanoiTower::reflect(clever::Field<int> &f)
{
	
	
#ifdef DEBUG
	
	if( !d_.first || !d_.second || !d_.third )
	{
		throw "invalid data(HanoiTower)";
	}

	if(
		!f.d ||
		f.h < d_.height ||
		f.w < 3u*( 1u + 2u*( d_.height - 1u ) ) + 2u
	)
		throw "invalid size of filed";
#endif
	f.clear(0);

	int *towers[] = {
		d_.first, d_.second, d_.third
	};
	int pos = 0;

	int *begin, *end;

	{
		lock_guard<mutex> guard(datamutex_);
		for(auto tow : towers)
		{
			for(size_t disk = 0u; disk < d_.height; ++disk)
			{
				if(tow[disk] == 0)
					break;
				begin = &f.at(
					pos + d_.height-1 - (tow[disk]-1),
					(f.h-disk-1)
				);
				end = begin + ( 1 + 2*(tow[disk]-1) );
				while(begin != end)
				{
					*begin = 1;
					++begin;
				}
			}

			pos += 1 + 2*(d_.height-1) + 1;
		}
	}


	return *this;
}






HanoiTower &HanoiTower::setData(HanoiTowerData const &data)
{
	free_();
	d_ = data;
	return *this;
}

HanoiTower &HanoiTower::releaseData()
{
	d_.first = nullptr;
	d_.second = nullptr;
	d_.third = nullptr;
	return *this;
}

HanoiTowerData const &HanoiTower::getData() const
{
	return d_;
}






bool HanoiTower::work_implement_(HanoiTowerData *d, int from, int to)
{
	constexpr unsigned int const SLEEP_DURATION = 500;



	
	if(d->height == 1)
	{
		{
			lock_guard<mutex> pauselock(pausemutex_);
		}
		if(interrupt_.exchange(false))
			return false;
		{
			lock_guard<mutex> datalock(mutex);
			*d->get(to) = *d->get(from);
			*d->get(from) = 0;
		}
		this_thread::sleep_for(
			chrono::milliseconds( SLEEP_DURATION )
		);
		return true;
	}



	
	int other;
	if(from != 0 && to != 0)
		other = 0;
	else if(from != 1 && to != 1)
		other = 1;
	else
		other = 2;



	
	HanoiTowerData dat;
	dat.first = d->get(from)+1;
	dat.second = d->get(other);
	dat.third = d->get(to);
	dat.height = d->height-1;

	if(!work_implement_(&dat, 0, 1))
		return false;

	
	{
		lock_guard<mutex> pauselock(pausemutex_);
	}
	if(interrupt_.exchange(false))
		return false;
	{
		lock_guard<mutex> datalock(datamutex_);
		*d->get(to) = *d->get(from);
		*d->get(from) = 0;
	}
	this_thread::sleep_for(
		chrono::milliseconds( SLEEP_DURATION )
	);

	
	dat.first = d->get(other);
	dat.second = d->get(to)+1;
	dat.third = d->get(from);
	dat.height = d->height-1;

	if(!work_implement_(&dat, 0, 1))
		return false;



	
	return true;
}

void HanoiTower::free_()
{
	if(d_.first)
		delete[] d_.first;
	if(d_.second)
		delete[] d_.second;
	if(d_.third)
		delete[] d_.third;
	return;
}






