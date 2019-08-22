ICON_FOLDER := ../../../icons

ICONS_APPS := notepad
ICONS_ACTIONS_32 := 
ICONS_ACTIONS_16 := filenew fileopen filesave filesaveas editcut editcopy editpaste

EXTRA_RESC_FILES := app.inf icons.inf

$(shell mkdir -p resc/icons)

ICON_DST_template = $(addsuffix _$(2).png, $(addprefix resc/icons/, $(1)))
ICON_SRC_template = $(addsuffix .png, $(addprefix $(ICON_FOLDER)/$(2)/$(3)/, $(1)))

define ICON_template=
$(call ICON_DST_template,$(1),$(2),$(3)): $(call ICON_SRC_template,$(1),$(2),$(3)) 
	cp $$< $$@

$(RESC-TAR-NAME): $(call ICON_DST_template,$(1),$(2),$(3))
endef

$(foreach ICON, $(ICONS_APPS), $(eval $(call ICON_template,$(ICON),32,apps)))
$(foreach ICON, $(ICONS_APPS), $(eval $(call ICON_template,$(ICON),16,apps)))

$(foreach ICON, $(ICONS_ACTIONS_32), $(eval $(call ICON_template,$(ICON),32,actions)))
$(foreach ICON, $(ICONS_ACTIONS_16), $(eval $(call ICON_template,$(ICON),16,actions)))

EXTRA_DST_template = $(addprefix resc/, $(1))

define EXTRA_template=
$(call EXTRA_DST_template,$(1)): $(1)
	cp $$< $$@

$(RESC-TAR-NAME): $(call EXTRA_DST_template,$(1))
endef

$(foreach EXTRA, $(EXTRA_RESC_FILES), $(eval $(call EXTRA_template,$(EXTRA))))

$(RESC-TAR-NAME): resc.mk
