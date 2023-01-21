
#ifndef _H_SST_MIRANDA_SAXPY_BENCH_GEN
#define _H_SST_MIRANDA_SAXPY_BENCH_GEN

#include <sst/elements/miranda/mirandaGenerator.h>
#include <sst/core/output.h>

#include <queue>

using namespace SST::RNG;

namespace SST {
namespace Miranda {


class SAXPYGenerator : public RequestGenerator {

public:
        SAXPYGenerator( ComponentId_t id, Params& params ) : RequestGenerator(id, params) { build(params); }

        void build(Params& params) {
		const uint32_t verbose = params.find<uint32_t>("verbose", 0);
		out = new Output("SAXPYGenerator[@p:@l]: ", verbose, 0, Output::STDOUT);

		vecN = params.find<uint64_t>("vec_n", 10000);

		elementWidth    = params.find<uint64_t>("element_width", 8);

		uint64_t nextStartAddr =  params.find<uint64_t>("nextStartAddr", 0);

                // X vector has Nx elements of size elementWidth
		xVecStartAddr = params.find<uint64_t>("x_start_addr", nextStartAddr);
		nextStartAddr += vecN * elementWidth;

                // Y vector has Ny elements of size elementWidth
		yVecStartAddr = params.find<uint64_t>("y_start_addr", nextStartAddr);

		
		
        iterations = params.find<uint64_t>("iterations", 1);
	}

	~SAXPYGenerator() {
		delete out;
	}

	void generate(MirandaRequestQueue<GeneratorRequest*>* q) {
		for(uint64_t i = 0; i < vecN; i++) {
			// add read for x[i]

			MemoryOpRequest* read_a  = new MemoryOpRequest(xVecStartAddr + i*elementWidth,elementWidth, READ);
            MemoryOpRequest* read_b = new MemoryOpRequest(yVecStartAddr + i*elementWidth,elementWidth, READ);
            MemoryOpRequest* write_b = new MemoryOpRequest(yVecStartAddr + i*elementWidth,elementWidth, WRITE);

			write_b->addDependency(read_a->getRequestID());
			write_b->addDependency(read_b->getRequestID());

			out->verbose(CALL_INFO, 8, 0, "Issuing READ request for address %" PRIu64 "\n", (xVecStartAddr + i*elementWidth));
			q->push_back(read_a);

			out->verbose(CALL_INFO, 8, 0, "Issuing READ request for address %" PRIu64 "\n", (yVecStartAddr + i*elementWidth));
			q->push_back(read_b);

			out->verbose(CALL_INFO, 8, 0, "Issuing WRITE request for address %" PRIu64 "\n", (xVecStartAddr + i*elementWidth));
			q->push_back(write_b);

		}
        iterations--;
	}

    bool isFinished() {
		return (0 == iterations);
	}
    void completed() {}
    SST_ELI_REGISTER_SUBCOMPONENT_DERIVED(
                SAXPYGenerator,
                "miranda",
                "SAXPYGenerator",
                SST_ELI_ELEMENT_VERSION(1,0,0),
		"Creates a linear matrix access pattern",
                SST::Miranda::RequestGenerator
        )

 	SST_ELI_DOCUMENT_PARAMS(
		{ "vecN",	"The number of elements ", "10000" },
    		{ "elementWidth",  "Sets the width of one matrix element, typically 8 for a double", "8" },
    		{ "xVecStartAddr", "Sets the start address of the A vector", "0" },
    		{ "yVecStartAddr", "Sets the start address of the B vector", "10000" },
    		{ "iterations",     "Sets the number of repeats to perform" }
        ) 

private:
	Output* out;
	uint64_t vecN;
	uint64_t elementWidth;
	uint64_t xVecStartAddr;
	uint64_t yVecStartAddr;
	uint64_t iterations;
	
};
}
}


#endif