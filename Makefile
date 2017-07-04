CC=gcc
RM=rm -f

CFLAGS = -Wall

# ============================================================================

COMMON_SOURCES_DIR = src/common/main/
COMMON_SOURCES = AlphabetTransform.c
COMMON_SOURCES += Chi2Decode.c
COMMON_SOURCES += CommonCLAP.c
COMMON_SOURCES += CosetFunctions.c
COMMON_SOURCES += FileUtils.c
COMMON_SOURCES += FrequencyInfo.c
COMMON_SOURCES += IndexOfCoincidence.c

COMMON_SOURCES_FP = $(addprefix $(COMMON_SOURCES_DIR),$(COMMON_SOURCES))

COMMON_OBJ = $(COMMON_SOURCES:.c=.o)
COMMON_OBJ_DIR = build/common_obj/
COMMON_OBJ_FP = $(addprefix $(COMMON_OBJ_DIR),$(COMMON_OBJ))

COMMON_INCLUDES += -I $(COMMON_SOURCES_DIR)

common: $(COMMON_OBJ_FP)

$(COMMON_OBJ_DIR)%.o: $(COMMON_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(COMMON_INCLUDES)

clean_common:
	-$(RM) $(COMMON_OBJ_FP)

# ============================================================================

COMMON_TEST_SOURCES_DIR = src/common/test/
COMMON_TEST_SOURCES = main.c
COMMON_TEST_SOURCES += TestChi2Decode.c
COMMON_TEST_SOURCES += TestCommonCLAP.c
COMMON_TEST_SOURCES += TestCosetFunctions.c
COMMON_TEST_SOURCES += TestFileUtils.c
COMMON_TEST_SOURCES += TestFrequencyInfo.c
COMMON_TEST_SOURCES += TestIndexOfCoincidence.c

COMMON_TEST_OBJ = $(COMMON_TEST_SOURCES:.c=.o)
COMMON_TEST_OBJ_DIR = build/common_test_obj/
COMMON_TEST_OBJ_FP = $(addprefix $(COMMON_TEST_OBJ_DIR),$(COMMON_TEST_OBJ))

COMMON_TEST_INCLUDES = -I $(COMMON_TEST_SOURCES_DIR)
COMMON_TEST_INCLUDES += -I $(COMMON_SOURCES_DIR)

COMMON_TEST_EXECUTABLE = vi_test_common
ifeq ($(OS), Windows_NT)
	COMMON_TEST_EXECUTABLE = vi_test_common.exe
endif

COMMON_TEST_EXECUTABLE_DIR = build/testbin/
COMMON_TEST_EXECUTABLE_FP = $(addprefix $(COMMON_TEST_EXECUTABLE_DIR),$(COMMON_TEST_EXECUTABLE))

common_test: common $(COMMON_TEST_OBJ_FP) $(COMMON_TEST_EXECUTABLE_FP)

$(COMMON_TEST_EXECUTABLE_FP): $(COMMON_TEST_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(COMMON_TEST_OBJ_FP) -o $@

$(COMMON_TEST_OBJ_DIR)%.o: $(COMMON_TEST_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(COMMON_TEST_INCLUDES)

clean_common_test: clean_common
	-$(RM) $(COMMON_TEST_OBJ_FP)
	-$(RM) $(COMMON_TEST_EXECUTABLE_FP)

# ============================================================================

DECODER_SOURCES_DIR = src/decoder/main/
DECODER_SOURCES = main.c
DECODER_SOURCES += Decoder.c
DECODER_SOURCES += DecoderCLAP.c

DECODER_OBJ = $(DECODER_SOURCES:.c=.o)
DECODER_OBJ_DIR = build/decoder_obj/
DECODER_OBJ_FP = $(addprefix $(DECODER_OBJ_DIR),$(DECODER_OBJ))

DECODER_INCLUDES = -I $(DECODER_SOURCES_DIR)
DECODER_INCLUDES += -I $(COMMON_SOURCES_DIR)

DECODER_EXECUTABLE = vi_decoder
ifeq ($(OS), Windows_NT)
	DECODER_EXECUTABLE = vi_decoder.exe
endif

DECODER_EXECUTABLE_DIR = build/bin/
DECODER_EXECUTABLE_FP = $(addprefix $(DECODER_EXECUTABLE_DIR),$(DECODER_EXECUTABLE))

decoder: common $(DECODER_OBJ_FP) $(DECODER_EXECUTABLE_FP)

$(DECODER_EXECUTABLE_FP): $(DECODER_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(DECODER_OBJ_FP) -o $@

$(DECODER_OBJ_DIR)%.o: $(DECODER_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(DECODER_INCLUDES)

clean_decoder: clean_common
	-$(RM) $(DECODER_OBJ_FP)
	-$(RM) $(DECODER_EXECUTABLE_FP)

# ============================================================================

ENCODER_SOURCES_DIR = src/encoder/main/
ENCODER_SOURCES = main.c
ENCODER_SOURCES += Encoder.c
ENCODER_SOURCES += EncoderCLAP.c

ENCODER_OBJ = $(ENCODER_SOURCES:.c=.o)
ENCODER_OBJ_DIR = build/encoder_obj/
ENCODER_OBJ_FP = $(addprefix $(ENCODER_OBJ_DIR),$(ENCODER_OBJ))

ENCODER_INCLUDES = -I $(ENCODER_SOURCES_DIR)
ENCODER_INCLUDES += -I $(COMMON_SOURCES_DIR)

ENCODER_EXECUTABLE = vi_encoder
ifeq ($(OS), Windows_NT)
	ENCODER_EXECUTABLE = vi_encoder.exe
endif
ENCODER_EXECUTABLE_DIR = build/bin/
ENCODER_EXECUTABLE_FP = $(addprefix $(ENCODER_EXECUTABLE_DIR),$(ENCODER_EXECUTABLE))

encoder: common $(ENCODER_OBJ_FP) $(ENCODER_EXECUTABLE_FP)

$(ENCODER_EXECUTABLE_FP): $(ENCODER_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(ENCODER_OBJ_FP) -o $@

$(ENCODER_OBJ_DIR)%.o: $(ENCODER_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(ENCODER_INCLUDES)

clean_encoder: clean_common
	-$(RM) $(ENCODER_OBJ_FP)
	-$(RM) $(ENCODER_EXECUTABLE_FP)

# ============================================================================

PREPROCESSOR_SOURCES_DIR = src/preprocessor/main/
PREPROCESSOR_SOURCES = main.c
PREPROCESSOR_SOURCES += Preprocessor.c
PREPROCESSOR_SOURCES += PreprocessorCLAP.c

PREPROCESSOR_OBJ = $(PREPROCESSOR_SOURCES:.c=.o)
PREPROCESSOR_OBJ_DIR = build/preprocessor_obj/
PREPROCESSOR_OBJ_FP = $(addprefix $(PREPROCESSOR_OBJ_DIR),$(PREPROCESSOR_OBJ))

PREPROCESSOR_INCLUDES = -I $(PREPROCESSOR_SOURCES_DIR)
PREPROCESSOR_INCLUDES = -I $(COMMON_SOURCES_DIR)

PREPROCESSOR_EXECUTABLE = vi_preprocessor
ifeq ($(OS), Windows_NT)
	PREPROCESSOR_EXECUTABLE = vi_preprocessor.exe
endif
PREPROCESSOR_EXECUTABLE_DIR = build/bin/
PREPROCESSOR_EXECUTABLE_FP = $(addprefix $(PREPROCESSOR_EXECUTABLE_DIR),$(PREPROCESSOR_EXECUTABLE))

preprocessor: common $(PREPROCESSOR_OBJ_FP) $(PREPROCESSOR_EXECUTABLE_FP)

$(PREPROCESSOR_EXECUTABLE_FP): $(PREPROCESSOR_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(PREPROCESSOR_OBJ_FP) -o $@

$(PREPROCESSOR_OBJ_DIR)%.o: $(PREPROCESSOR_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(PREPROCESSOR_INCLUDES)

clean_preprocessor: clean_common
	-$(RM) $(PREPROCESSOR_OBJ_FP)
	-$(RM) $(PREPROCESSOR_EXECUTABLE_FP)

# ============================================================================

BREAKER_SOURCES_DIR = src/breaker/main/
BREAKER_SOURCES = main.c
BREAKER_SOURCES += Breaker.c
BREAKER_SOURCES += BreakerCLAP.c

BREAKER_OBJ = $(BREAKER_SOURCES:.c=.o)
BREAKER_OBJ_DIR = build/breaker_obj/
BREAKER_OBJ_FP = $(addprefix $(BREAKER_OBJ_DIR),$(BREAKER_OBJ))

BREAKER_INCLUDES = -I $(BREAKER_SOURCES_DIR)
BREAKER_INCLUDES = -I $(COMMON_SOURCES_DIR)

BREAKER_EXECUTABLE = vi_breaker
ifeq ($(OS), Windows_NT)
	BREAKER_EXECUTABLE = vi_breaker.exe
endif
BREAKER_EXECUTABLE_DIR = build/bin/
BREAKER_EXECUTABLE_FP = $(addprefix $(BREAKER_EXECUTABLE_DIR),$(BREAKER_EXECUTABLE))

breaker: common $(BREAKER_OBJ_FP) $(BREAKER_EXECUTABLE_FP)

$(BREAKER_EXECUTABLE_FP): $(BREAKER_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(BREAKER_OBJ_FP) -o $@

$(BREAKER_OBJ_DIR)%.o: $(BREAKER_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(BREAKER_INCLUDES)

clean_breaker: clean_common
	-$(RM) $(BREAKER_OBJ_FP)
	-$(RM) $(BREAKER_EXECUTABLE_FP)

# ============================================================================

CHI2BREAKER_SOURCES_DIR = src/chi2breaker/main/
CHI2BREAKER_SOURCES = main.c
CHI2BREAKER_SOURCES += Chi2Breaker.c
CHI2BREAKER_SOURCES += Chi2BreakerCLAP.c

CHI2BREAKER_OBJ = $(CHI2BREAKER_SOURCES:.c=.o)
CHI2BREAKER_OBJ_DIR = build/chi2breaker_obj/
CHI2BREAKER_OBJ_FP = $(addprefix $(CHI2BREAKER_OBJ_DIR),$(CHI2BREAKER_OBJ))

CHI2BREAKER_INCLUDES = -I $(CHI2BREAKER_SOURCES_DIR)
CHI2BREAKER_INCLUDES += -I $(COMMON_SOURCES_DIR)

CHI2BREAKER_EXECUTABLE = vi_chi2breaker
ifeq ($(OS), Windows_NT)
	CHI2BREAKER_EXECUTABLE = vi_chi2breaker.exe
endif
CHI2BREAKER_EXECUTABLE_DIR = build/bin/
CHI2BREAKER_EXECUTABLE_FP = $(addprefix $(CHI2BREAKER_EXECUTABLE_DIR),$(CHI2BREAKER_EXECUTABLE))

chi2breaker: common $(CHI2BREAKER_OBJ_FP) $(CHI2BREAKER_EXECUTABLE_FP)

$(CHI2BREAKER_EXECUTABLE_FP): $(CHI2BREAKER_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(CHI2BREAKER_OBJ_FP) -o $@

$(CHI2BREAKER_OBJ_DIR)%.o: $(CHI2BREAKER_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(CHI2BREAKER_INCLUDES)

clean_chi2breaker: clean_common
	-$(RM) $(CHI2BREAKER_OBJ_FP)
	-$(RM) $(CHI2BREAKER_EXECUTABLE_FP)

# ============================================================================

CHI2BREAKER_TEST_SOURCES_DIR = src/chi2breaker/test/
CHI2BREAKER_TEST_SOURCES = main.c
#CHI2BREAKER_TEST_SOURCES += TestChi2Breaker.c

CHI2BREAKER_TEST_OBJ = $(CHI2BREAKER_TEST_SOURCES:.c=.o)
CHI2BREAKER_TEST_OBJ_DIR = build/chi2breaker_test_obj/
CHI2BREAKER_TEST_OBJ_FP = $(addprefix $(CHI2BREAKER_TEST_OBJ_DIR),$(CHI2BREAKER_TEST_OBJ))

CHI2BREAKER_TEST_INCLUDES = -I $(CHI2BREAKER_SOURCES_DIR)
CHI2BREAKER_TEST_INCLUDES += -I $(CHI2BREAKER_TEST_SOURCES_DIR)
CHI2BREAKER_TEST_INCLUDES += -I $(COMMON_SOURCES_DIR)

CHI2BREAKER_TEST_EXECUTABLE = vi_test_chi2breaker
ifeq ($(OS), Windows_NT)
	CHI2BREAKER_EXECUTABLE = vi_test_chi2breaker.exe
endif
CHI2BREAKER_TEST_EXECUTABLE_DIR = build/testbin/
CHI2BREAKER_TEST_EXECUTABLE_FP = $(addprefix $(CHI2BREAKER_TEST_EXECUTABLE_DIR),$(CHI2BREAKER_TEST_EXECUTABLE))

#CHI2BREAKER_OBJ_FP_FILTERED = $(filter-out $(wildcard */main.o), $(CHI2BREAKER_OBJ_FP))
CHI2BREAKER_OBJ_FP_FILTERED = $(filter-out build/chi2breaker_obj/main.o, $(CHI2BREAKER_OBJ_FP))

chi2breaker_test: common chi2breaker $(CHI2BREAKER_TEST_OBJ_FP) $(CHI2BREAKER_TEST_EXECUTABLE_FP)

$(CHI2BREAKER_TEST_EXECUTABLE_FP): $(CHI2BREAKER_TEST_OBJ_FP)
	$(CC) $(COMMON_OBJ_FP) $(CHI2BREAKER_OBJ_FP_FILTERED) $(CHI2BREAKER_TEST_OBJ_FP) -o $@

$(CHI2BREAKER_TEST_OBJ_DIR)%.o: $(CHI2BREAKER_TEST_SOURCES_DIR)%.c
	$(CC) -c $< -o $@  $(CFLAGS) $(CHI2BREAKER_TEST_INCLUDES)

clean_chi2breaker_test: clean_common clean_common_test clean_chi2breaker
	-$(RM) $(CHI2BREAKER_TEST_OBJ_FP)
	-$(RM) $(CHI2BREAKER_TEST_EXECUTABLE_FP)

# ============================================================================

all: breaker chi2breaker decoder encoder preprocessor

# ============================================================================

CLEAN_TARGETS =  clean_common
CLEAN_TARGETS += clean_common_test
CLEAN_TARGETS += clean_breaker
CLEAN_TARGETS += clean_chi2breaker
CLEAN_TARGETS += clean_chi2breaker_test
CLEAN_TARGETS += clean_decoder
CLEAN_TARGETS += clean_encoder
CLEAN_TARGETS += clean_preprocessor

clean: $(CLEAN_TARGETS)

# ============================================================================

TEST_TARGETS = common_test
TEST_TARGETS += chi2breaker_test

tests: $(TEST_TARGETS)

# ============================================================================
