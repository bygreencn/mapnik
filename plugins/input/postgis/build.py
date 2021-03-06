#
# This file is part of Mapnik (c++ mapping toolkit)
#
# Copyright (C) 2006 Artem Pavlenko, Jean-Francois Doyon
#
# Mapnik is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# $Id$

Import ('plugin_base')
Import ('env')

prefix = env['PREFIX']

plugin_env = plugin_base.Clone()

postgis_src = Split(
  """
        postgis_datasource.cpp
        postgis_featureset.cpp
  """
        )

# clear out and rebuild libs
plugin_env['LIBS'] = ['pq']

# Link Library to Dependencies
plugin_env['LIBS'].append('mapnik')
plugin_env['LIBS'].append(env['ICU_LIB_NAME'])
if env['THREADING'] == 'multi':
	plugin_env['LIBS'].append('boost_thread%s' % env['BOOST_APPEND'])

if env['RUNTIME_LINK'] == 'static':
    #cmd = 'pg_config --libs'
    #plugin_env.ParseConfig(cmd)
    # pg_config does not seem to report correct deps of libpq
    # so resort to hardcoding for now
    plugin_env['LIBS'].extend(['ldap','pam','ssl','crypto','krb5'])

input_plugin = plugin_env.SharedLibrary('../postgis', source=postgis_src, SHLIBPREFIX='', SHLIBSUFFIX='.input', LINKFLAGS=env['CUSTOM_LDFLAGS'])

# if the plugin links to libmapnik ensure it is built first
Depends(input_plugin, env.subst('../../../src/%s' % env['MAPNIK_LIB_NAME']))

if 'uninstall' not in COMMAND_LINE_TARGETS:
    env.Install(env['MAPNIK_INPUT_PLUGINS_DEST'], input_plugin)
    env.Alias('install', env['MAPNIK_INPUT_PLUGINS_DEST'])
