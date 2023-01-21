
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

		
		scalarVal = params.find<double>("scalarVal", 2.0);
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
            MemoryOpRequest* write_Res = new MemoryOpRequest(yVecStartAddr + i*elementWidth,elementWidth, WRITE);

			write_Res->addDependency(read_a->getRequestID());
			write_Res->addDependency(read_b->getRequestID());

			out->verbose(CALL_INFO, 8, 0, "Issuing READ request for address %" PRIu64 "\n", (xVecStartAddr + i*elementWidth));
			q->push_back(read_a);

			out->verbose(CALL_INFO, 8, 0, "Issuing READ request for address %" PRIu64 "\n", (yVecStartAddr + i*elementWidth));
			q->push_back(read_b);

			out->verbose(CALL_INFO, 8, 0, "Issuing WRITE request for address %" PRIu64 "\n", (xVecStartAddr + i*elementWidth));
			q->push_back(write_Res);

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
		{ "matrix_nx",	"Sets the horizontal dimension of the matrix", "10" },
    		{ "matrix_ny",      "Sets the vertical dimension of the matrix (the number of rows)", "10" },
    		{ "elementWidth",  "Sets the width of one matrix element, typically 8 for a double", "8" },
    		{ "lhs_start_addr", "Sets the start address of the LHS vector", "0" },
    		{ "rhs_start_addr", "Sets the start address of the RHS vector", "80" },
    		{ "local_row_start", "Sets the row at which this generator will start processing", "0" },
    		{ "local_row_end",  "Sets the end at which rows will be processed by this generator", "10" },
    		{ "ordinal_width",  "Sets the width of ordinals (indices) in the matrix, typically 4 or 8", "8"},
    		{ "matrix_row_indices_start_addr", "Sets the row indices start address for the matrix", "0" },
    		{ "matrix_col_indices_start_addr", "Sets the col indices start address for the matrix", "0" },
    		{ "matrix_element_start_addr", "Sets the start address of the elements array", "0" },
    		{ "iterations",     "Sets the number of repeats to perform" },
    		{ "matrix_nnz_per_row", "Sets the number of non-zero elements per row", "9" }
        ) 

private:
	Output* out;
	uint64_t vecN;
	uint64_t elementWidth;
	uint64_t xVecStartAddr;
	uint64_t yVecStartAddr;
	uint64_t iterations;
	double scalarVal;
};
}
}


#endif