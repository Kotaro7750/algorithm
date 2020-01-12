# BenchMark
## about
BenchMark is a class to measure duration time for evaluate some algorithm.

## usage

###  void BenchMark::Start()
Start measurement.

### long BenchMark::Lap()
Save lap time and return an index of saved lap time. 
To get saved lap time,you need to use BenchMark::getLap().

### long BenchMark::getLap(long index)
Return a lap time[ms] indicated by index.
You can use either getLapUS() to get time[us] and getLapNS() to get time[ns]

### long BenchMark::Stop()
Stoop measurement ,save lap time and return an index of saved lap time.
