AM_DEFAULT_SOURCE_EXT = .cpp
AM_CPPFLAGS = -iquote ${top_srcdir}

sbin_PROGRAMS = \
	phosphor-power-psu

phosphor_power_psu_SOURCES = \
	main.cpp \
	argument.cpp \
	power_supply.cpp

phosphor_power_psu_CXXFLAGS = \
	$(SDBUSPLUS_CFLAGS) \
	$(PHOSPHOR_LOGGING_CFLAGS) \
	${PHOSPHOR_DBUS_INTERFACES_CFLAGS}

phosphor_power_psu_LDADD = \
	${top_builddir}/libpower.la \
	$(SDBUSPLUS_LIBS) \
	$(PHOSPHOR_LOGGING_LIBS) \
	${PHOSPHOR_DBUS_INTERFACES_LIBS}

# vim: tabstop=8 noexpandtab
