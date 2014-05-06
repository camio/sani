NAME:=sani
include ../smake/lib.mk

QMAKEDEFS = \
 BOOST_PATH="$(BOOST_PATH)" \
 SBASE_PATH="$(SBASE_PATH)"

# We depend on all of these because use of the POST_TARGETDEFS command in qmake
# requires them to be there.
$(eval $(call add-library-dependency,$(SBASE_PATH),sbase))
