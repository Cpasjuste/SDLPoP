PHONY := all package clean

DATE := $(shell date +%y-%m-%d)

CC := arm-vita-eabi-gcc
CXX := arm-vita-eabi-g++
STRIP := arm-vita-eabi-strip

PROJECT_TITLE := Prince Of Persia
PROJECT_TITLEID := PRINCEPER
PROJECT := vpop

LIBS = -lpsp2shell -lpthread -lSDL2 -lSDL2_image -lSDL2_mixer -lvorbis -lvorbisfile -logg \
		-lvita2d -lSceDisplay_stub -lSceGxm_stub \
		-lSceSysmodule_stub -lSceCtrl_stub -lScePgf_stub -lSceNetCtl_stub \
		-lSceNet_stub -lScePower_stub -lSceKernel_stub -lSceCommonDialog_stub \
		-lSceAppUtil_stub -lSceAudio_stub -lSceAppMgr_stub -lpng -ljpeg -lz -lm -lc


CFLAGS  = -Wl,-q -O3 -Wall \
			-march=armv7-a -mtune=cortex-a9 -mfpu=neon -mfloat-abi=hard \
			-DPSP2 -std=gnu99 -I$(VITASDK)/arm-vita-eabi/include

OBJS := main.o data.o seg000.o seg001.o seg002.o seg003.o seg004.o \
	seg005.o seg006.o seg007.o seg008.o seg009.o seqtbl.o replay.o options.o \
	strtoumax.o strtoimax.o

all: package

package: $(PROJECT).vpk

$(PROJECT).vpk: eboot.bin param.sfo
	rm -rf vpk && mkdir -p vpk/sce_sys/livearea/contents
	cp eboot.bin vpk/
	cp param.sfo vpk/sce_sys/
	cp ../*.DAT vpk/
	cp -r ../data vpk/data
	cd vpk && zip -r ../$(PROJECT)-$(DATE).vpk . && cd ..
#	cp vita/icon0.png vpk/sce_sys/
#	cp vita/template.xml vpk/sce_sys/livearea/contents/
#	cp vita/bg.png vpk/sce_sys/livearea/contents/
#	cp vita/startup.png vpk/sce_sys/livearea/contents/
	
eboot.bin: $(PROJECT).velf
	vita-make-fself $(PROJECT).velf eboot.bin

param.sfo:
	vita-mksfoex -s TITLE_ID="$(PROJECT_TITLEID)" "$(PROJECT_TITLE)" param.sfo

$(PROJECT).velf: $(PROJECT).elf
	$(STRIP) -g $<
	vita-elf-create $< $@

$(PROJECT).elf: $(OBJS)
	$(CC) -Wl,-q -o $@ $^ $(LIBS)

$(OBJ_DIRS):
	mkdir -p $@

out/%.o : src/%.c | $(OBJ_DIRS)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROJECT).velf $(PROJECT).elf *.vpk param.sfo eboot.bin $(OBJS)
	rm -rf vpk
