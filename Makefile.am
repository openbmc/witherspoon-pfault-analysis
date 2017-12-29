AM_DEFAULT_SOURCE_EXT = .cpp
if !INSTALL_ERROR_YAML
noinst_LTLIBRARIES = libpower.la
libpower_la_LDFLAGS = -static
libpower_la_LIBADD = \
	-lstdc++fs \
	$(PHOSPHOR_LOGGING_LIBS) \
	$(SDBUSPLUS_LIBS) \
	$(PHOSPHOR_DBUS_INTERFACES_LIBS)
libpower_la_CXXFLAGS = \
	$(PHOSPHOR_LOGGING_CFLAGS) \
	$(SDBUSPLUS_CFLAGS) \
	$(PHOSPHOR_DBUS_INTERFACES_CFLAGS)

libpower_la_SOURCES = \
	pmbus.cpp \
	timer.cpp \
	utility.cpp \
	org/open_power/Witherspoon/Fault/error.cpp

nobase_nodist_include_HEADERS = \
	org/open_power/Witherspoon/Fault/error.hpp

BUILT_SOURCES = \
	org/open_power/Witherspoon/Fault/error.cpp \
	org/open_power/Witherspoon/Fault/error.hpp

if GEN_ERRORS
nobase_nodist_include_HEADERS += \
                 phosphor-logging/elog-errors.hpp
BUILT_SOURCES += phosphor-logging/elog-errors.hpp
endif

org/open_power/Witherspoon/Fault/error.hpp: ${srcdir}/org/open_power/Witherspoon/Fault.errors.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS) -r $(srcdir) error exception-header org.open_power.Witherspoon.Fault > $@

org/open_power/Witherspoon/Fault/error.cpp: ${srcdir}/org/open_power/Witherspoon/Fault.errors.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS) -r $(srcdir) error exception-cpp org.open_power.Witherspoon.Fault > $@

SUBDIRS = . power-sequencer power-supply test
endif
# Export error YAML to shared location
yamldir = ${datadir}/phosphor-dbus-yaml/yaml
nobase_yaml_DATA = \
	org/open_power/Witherspoon/Fault.errors.yaml \
	org/open_power/Witherspoon/Fault.metadata.yaml

# Generate phosphor-logging/elog-errors.hpp
if GEN_ERRORS
ELOG_MAKO ?= elog-gen-template.mako.hpp
ELOG_DIR ?= ${OECORE_NATIVE_SYSROOT}${datadir}/phosphor-logging/elog
ELOG_GEN_DIR ?= ${ELOG_DIR}/tools/
ELOG_MAKO_DIR ?= ${ELOG_DIR}/tools/phosphor-logging/templates/
YAML_DIR ?= ${OECORE_NATIVE_SYSROOT}${datadir}/phosphor-dbus-yaml/yaml
phosphor-logging/elog-errors.hpp:
	@mkdir -p ${YAML_DIR}/org/open_power/Witherspoon/
	@cp ${top_srcdir}/org/open_power/Witherspoon/Fault.errors.yaml ${YAML_DIR}/org/open_power/Witherspoon/Fault.errors.yaml
	@cp ${top_srcdir}/org/open_power/Witherspoon/Fault.metadata.yaml ${YAML_DIR}/org/open_power/Witherspoon/Fault.metadata.yaml
	@mkdir -p `dirname $@`
	@chmod 777 $(ELOG_GEN_DIR)/elog-gen.py
	$(AM_V_at)$(PYTHON) $(ELOG_GEN_DIR)/elog-gen.py -y ${YAML_DIR} -t ${ELOG_MAKO_DIR} -m ${ELOG_MAKO} -o $@
endif