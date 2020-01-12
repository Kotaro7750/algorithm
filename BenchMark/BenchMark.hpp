#include <chrono>
#include <vector>

class BenchMark {

public:
  BenchMark();
  void Start();
  long Stop();
  long Lap();
  long getLap(long);
  long getLapUS(long);
  long getLapNS(long);

private:
  std::chrono::system_clock::time_point startTime;
  std::chrono::system_clock::time_point endTime;
  std::chrono::system_clock::time_point prevLapTime;
  std::vector<std::chrono::system_clock::duration> lap;
};

BenchMark::BenchMark() {}

void BenchMark::Start() { startTime = std::chrono::system_clock::now(); }
long BenchMark::Stop() {
  long index = Lap();
  endTime = prevLapTime;
  return index;
}

long BenchMark::Lap() {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  std::chrono::system_clock::duration lapDuration =
      (lap.size() == 0 ? now - startTime : now - prevLapTime);

  prevLapTime = now;

  lap.push_back(lapDuration);

  return lap.size() - 1;
}

long BenchMark::getLap(long i) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(lap[i]).count();
}

long BenchMark::getLapUS(long i) {
  return std::chrono::duration_cast<std::chrono::microseconds>(lap[i]).count();
}

long BenchMark::getLapNS(long i) {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(lap[i]).count();
}
