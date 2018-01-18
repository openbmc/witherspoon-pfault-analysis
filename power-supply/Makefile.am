AM_DEFAULT_SOURCE_EXT = .cpp
AM_CPPFLAGS = -iquote ${top_srcdir}

sbin_PROGRAMS = \
	witherspoon-psu-monitor

witherspoon_psu_monitor_SOURCES = \
	main.cpp \
	argument.cpp \
	power_supply.cpp \
	record_manager.cpp \
	org/open_power/Sensor/Aggregation/History/Maximum/server.cpp \
	org/open_power/Sensor/Aggregation/History/Average/server.cpp

witherspoon_psu_monitor_CXXFLAGS = \
	$(SDBUSPLUS_CFLAGS) \
	$(PHOSPHOR_LOGGING_CFLAGS) \
	${PHOSPHOR_DBUS_INTERFACES_CFLAGS}

witherspoon_psu_monitor_LDADD = \
	${top_builddir}/libpower.la \
	$(SDBUSPLUS_LIBS) \
	$(PHOSPHOR_LOGGING_LIBS) \
	${PHOSPHOR_DBUS_INTERFACES_LIBS}

