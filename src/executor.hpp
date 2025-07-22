#ifndef EXECUTOR_DV_H
#define EXECUTOR_DV_H
namespace emulator {
	class executor {
		public:
		void run();
		executor(registersManager regManager, memoryManager memManager);
	}
}
#endif
