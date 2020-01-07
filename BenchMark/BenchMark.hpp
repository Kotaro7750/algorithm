#include <chrono>
#include <vector>

class BenchMark {

public:
  BenchMark();
  void Start();
  void Stop();
  long Lap();
  long getLap(long);

private:
  std::chrono::system_clock::time_point startTime;
  std::chrono::system_clock::time_point endTime;
  std::chrono::system_clock::time_point prevLapTime;
  std::vector<std::chrono::system_clock::duration> lap;
};

BenchMark::BenchMark() {}

void BenchMark::Start() { startTime = std::chrono::system_clock::now(); }
void BenchMark::Stop() {
  Lap();
  endTime = prevLapTime;
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
