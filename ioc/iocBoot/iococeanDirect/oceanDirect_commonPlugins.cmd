# This is an example file for creating plugins
# It uses the following environment variable macros
# Many of the parameters defined in this file are also in commonPlugins_settings.req so if autosave is being
# use the autosave value will replace the value passed to this file.

# $(PREFIX)      Prefix for all records
# $(PORT)        The port name for the detector.  In autosave.
# $(QSIZE)       The queue size for all plugins.  In autosave.
# $(XSIZE)       The maximum image width; used to set the maximum size for row profiles in the NDPluginStats plugin and 1-D FFT
#                   profiles in NDPluginFFT.
# $(YSIZE)       The maximum image height; used to set the maximum size for column profiles in the NDPluginStats plugin
# $(NCHANS)      The maximum number of time series points in the NDPluginStats, NDPluginROIStats, and NDPluginAttribute plugins
# $(CBUFFS)      The maximum number of frames buffered in the NDPluginCircularBuff plugin
# $(MAX_THREADS) The maximum number of threads for plugins which can run in multiple threads. Defaults to 5.

# Create an HDF5 file saving plugin
NDFileHDF5Configure("FileHDF1", $(QSIZE), 0, "$(PORT)", 0)
dbLoadRecords("NDFileHDF5.template",  "P=$(PREFIX),R=HDF1:,PORT=FileHDF1,ADDR=0,TIMEOUT=1,XMLSIZE=2048,NDARRAY_PORT=$(PORT)")

# Create 8 ROIStat plugins
NDROIStatConfigure("ROISTAT1", $(QSIZE), 0, "$(PORT)", 0, 8, 0, 0, 0, 0, $(MAX_THREADS=5))
dbLoadRecords("NDROIStat.template",   "P=$(PREFIX),R=ROIStat1:  ,PORT=ROISTAT1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT),NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:1:,PORT=ROISTAT1,ADDR=0,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:2:,PORT=ROISTAT1,ADDR=1,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:3:,PORT=ROISTAT1,ADDR=2,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:4:,PORT=ROISTAT1,ADDR=3,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:5:,PORT=ROISTAT1,ADDR=4,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:6:,PORT=ROISTAT1,ADDR=5,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:7:,PORT=ROISTAT1,ADDR=6,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDROIStatN.template",  "P=$(PREFIX),R=ROIStat1:8:,PORT=ROISTAT1,ADDR=7,TIMEOUT=1,NCHANS=$(NCHANS)")

# Create a processing plugin
NDProcessConfigure("PROC1", $(QSIZE), 0, "$(PORT)", 0, 0, 0)
dbLoadRecords("NDProcess.template",   "P=$(PREFIX),R=Proc1:,  PORT=PROC1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
# Create a TIFF file plugin to read dark and flatfield images into the processing plugin
NDFileTIFFConfigure("PROC1TIFF", $(QSIZE), 0, "$(PORT)", 0)
dbLoadRecords("NDFileTIFF.template",  "P=$(PREFIX),R=Proc1:TIFF:,PORT=PROC1TIFF,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")

# Create a scatter plugin
#NDScatterConfigure("SCATTER1", $(QSIZE), 0, "$(PORT)", 0, 0, 0)
#dbLoadRecords("NDScatter.template",   "P=$(PREFIX),R=Scatter1:,  PORT=SCATTER1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")

# Create a gather plugin with 8 ports
#NDGatherConfigure("GATHER1", $(QSIZE), 0, 8, 0, 0)
#dbLoadRecords("NDGather.template",   "P=$(PREFIX),R=Gather1:, PORT=GATHER1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=1, PORT=GATHER1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=2, PORT=GATHER1,ADDR=1,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=3, PORT=GATHER1,ADDR=2,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=4, PORT=GATHER1,ADDR=3,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=5, PORT=GATHER1,ADDR=4,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=6, PORT=GATHER1,ADDR=5,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=7, PORT=GATHER1,ADDR=6,TIMEOUT=1,NDARRAY_PORT=$(PORT)")
#dbLoadRecords("NDGatherN.template",   "P=$(PREFIX),R=Gather1:, N=8, PORT=GATHER1,ADDR=7,TIMEOUT=1,NDARRAY_PORT=$(PORT)")

# Create a statistics plugin
NDStatsConfigure("STATS1", $(QSIZE), 0, "$(PORT)", 0, 0, 0, 0, 0, $(MAX_THREADS=5))
dbLoadRecords("NDStats.template",     "P=$(PREFIX),R=Stats1:,  PORT=STATS1,ADDR=0,TIMEOUT=1,HIST_SIZE=256,XSIZE=4000,YSIZE=1,NCHANS=1024,NDARRAY_PORT=$(PORT)")
NDTimeSeriesConfigure("STATS1_TS", $(QSIZE), 0, "STATS1", 1, 23)
dbLoadRecords("NDTimeSeries.template",  "P=$(PREFIX),R=Stats1:TS:, PORT=STATS1_TS,ADDR=0,TIMEOUT=1,NDARRAY_PORT=STATS1,NDARRAY_ADDR=1,NCHANS=$(NCHANS),ENABLED=1")

# Create an NDAttribute plugin with 8 attributes
NDAttrConfigure("ATTR1", $(QSIZE), 0, "$(PORT)", 0, 8, 0, 0, 0)
dbLoadRecords("NDAttribute.template",  "P=$(PREFIX),R=Attr1:,    PORT=ATTR1,ADDR=0,TIMEOUT=1,NCHANS=$(NCHANS),NDARRAY_PORT=$(PORT)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:1:,  PORT=ATTR1,ADDR=0,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:2:,  PORT=ATTR1,ADDR=1,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:3:,  PORT=ATTR1,ADDR=2,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:4:,  PORT=ATTR1,ADDR=3,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:5:,  PORT=ATTR1,ADDR=4,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:6:,  PORT=ATTR1,ADDR=5,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:7:,  PORT=ATTR1,ADDR=6,TIMEOUT=1,NCHANS=$(NCHANS)")
dbLoadRecords("NDAttributeN.template", "P=$(PREFIX),R=Attr1:8:,  PORT=ATTR1,ADDR=7,TIMEOUT=1,NCHANS=$(NCHANS)")
NDTimeSeriesConfigure("ATTR1_TS", $(QSIZE), 0, "ATTR1", 1, 8)
dbLoadRecords("NDTimeSeries.template",  "P=$(PREFIX),R=Attr1:TS:, PORT=ATTR1_TS,ADDR=0,TIMEOUT=1,NDARRAY_PORT=ATTR1,NDARRAY_ADDR=1,NCHANS=$(NCHANS),ENABLED=1")

