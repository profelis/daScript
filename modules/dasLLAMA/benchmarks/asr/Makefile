# ASR bench corpus. `make` builds the 4-file speed corpus; `make librispeech`
# adds the 25-clip short-utterance latency batch (346 MB one-time fetch).
#
# jfk/gb1 copy from a local whisper.cpp checkout when present, else fetch from
# the same pinned URLs whisper.cpp's Makefile uses. Everything lands as
# 16 kHz mono s16 WAV so every engine decodes identical input.

WHISPER_SAMPLES ?= $(HOME)/Work/whisper.cpp/samples
CORPUS := corpus

JFK_URL := https://raw.githubusercontent.com/ggml-org/whisper.cpp/master/samples/jfk.wav
GB1_URL := https://upload.wikimedia.org/wikipedia/commons/1/1f/George_W_Bush_Columbia_FINAL.ogg
HP0_URL := https://upload.wikimedia.org/wikipedia/en/d/d4/En.henryfphillips.ogg
LS_URL  := https://www.openslr.org/resources/12/test-clean.tar.gz
LS_CLIPS := 25

all: $(CORPUS)/jfk.wav $(CORPUS)/jfk3.wav $(CORPUS)/gb1.wav $(CORPUS)/hp0.wav $(CORPUS)/hp0x2.wav

$(CORPUS):
	mkdir -p $(CORPUS)

$(CORPUS)/jfk.wav: | $(CORPUS)
	@if [ -f $(WHISPER_SAMPLES)/jfk.wav ]; then cp $(WHISPER_SAMPLES)/jfk.wav $@; \
	else curl -L -o $@ $(JFK_URL); fi

# 33 s long-form fixture: jfk x3 (the whisper_plan jfk3 shape, regenerated)
$(CORPUS)/jfk3.wav: $(CORPUS)/jfk.wav
	printf "file 'jfk.wav'\nfile 'jfk.wav'\nfile 'jfk.wav'\n" > $(CORPUS)/jfk3.txt
	cd $(CORPUS) && ffmpeg -y -loglevel error -f concat -safe 0 -i jfk3.txt -c copy jfk3.wav
	rm $(CORPUS)/jfk3.txt

$(CORPUS)/gb1.wav: | $(CORPUS)
	@if [ -f $(WHISPER_SAMPLES)/gb1.wav ]; then cp $(WHISPER_SAMPLES)/gb1.wav $@; \
	else curl -L -o $(CORPUS)/gb1.ogg $(GB1_URL) && \
	     ffmpeg -y -loglevel error -i $(CORPUS)/gb1.ogg -ar 16000 -ac 1 -c:a pcm_s16le $@ && \
	     rm $(CORPUS)/gb1.ogg; fi

# ~13 min spoken-Wikipedia article (whisper.cpp's hp0 long sample)
$(CORPUS)/hp0.wav: | $(CORPUS)
	curl -L -o $(CORPUS)/hp0.ogg $(HP0_URL)
	ffmpeg -y -loglevel error -i $(CORPUS)/hp0.ogg -ar 16000 -ac 1 -c:a pcm_s16le $@
	rm $(CORPUS)/hp0.ogg

# ~9 min: hp0 x2 (the ~10-min throughput point; hp0 itself is 4:33)
$(CORPUS)/hp0x2.wav: $(CORPUS)/hp0.wav
	printf "file 'hp0.wav'\nfile 'hp0.wav'\n" > $(CORPUS)/hp0x2.txt
	cd $(CORPUS) && ffmpeg -y -loglevel error -f concat -safe 0 -i hp0x2.txt -c copy hp0x2.wav
	rm $(CORPUS)/hp0x2.txt

# 25 short LibriSpeech test-clean clips (deterministic: first 25 in sorted order)
librispeech: | $(CORPUS)
	mkdir -p $(CORPUS)/librispeech
	@if [ ! -d $(CORPUS)/LibriSpeech/test-clean ]; then \
	    curl -L -o $(CORPUS)/test-clean.tar.gz $(LS_URL) && \
	    tar xzf $(CORPUS)/test-clean.tar.gz -C $(CORPUS) && \
	    rm $(CORPUS)/test-clean.tar.gz; fi
	@n=0; for f in $$(find $(CORPUS)/LibriSpeech/test-clean -name '*.flac' | sort | head -$(LS_CLIPS)); do \
	    n=$$((n+1)); \
	    ffmpeg -y -loglevel error -i $$f -ar 16000 -ac 1 -c:a pcm_s16le \
	        $(CORPUS)/librispeech/$$(printf '%02d' $$n)_$$(basename $$f .flac).wav; \
	done; echo "$$n clips ready in $(CORPUS)/librispeech/"

clean:
	rm -rf $(CORPUS)

.PHONY: all librispeech clean
