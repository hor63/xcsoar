/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009

	M Roberts (original release)
	Robin Birch <robinb@ruffnready.co.uk>
	Samuel Gisiger <samuel.gisiger@triadis.ch>
	Jeff Goodenough <jeff@enborne.f2s.com>
	Alastair Harrison <aharrison@magic.force9.co.uk>
	Scott Penrose <scottp@dd.com.au>
	John Wharington <jwharington@gmail.com>
	Lars H <lars_hn@hotmail.com>
	Rob Dunning <rob@raspberryridgesheepfarm.com>
	Russell King <rmk@arm.linux.org.uk>
	Paolo Ventafridda <coolwind@email.it>
	Tobias Lohner <tobias@lohner-net.de>
	Mirek Jezek <mjezek@ipplc.cz>
	Max Kellermann <max@duempel.org>
	Tobias Bieniek <tobias.bieniek@gmx.de>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "Registry.hpp"
#include "StringUtil.hpp"
#include "LogFile.hpp"
#include "Defines.h"
#include "Sizes.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef WIN32
#include <gconf/gconf.h>
#endif

#ifdef WIN32
#define CONF(key) _T(key)
#else /* !WIN32 */
#define CONF(key) ("/apps/XCSoar/" key)
#endif

const TCHAR szProfileKey[] = CONF(REGKEYNAME);
const TCHAR *szProfileDisplayType[MAXINFOWINDOWS] = {
  CONF("Info0"),
  CONF("Info1"),
  CONF("Info2"),
  CONF("Info3"),
  CONF("Info4"),
  CONF("Info5"),
  CONF("Info6"),
  CONF("Info7"),
  CONF("Info8"),
  CONF("Info9"),
  CONF("Info10"),
  CONF("Info11"),
  CONF("Info12"),
  CONF("Info13"),
}; // pL

const TCHAR *szProfileColour[] = {
  CONF("Colour0"),
  CONF("Colour1"),
  CONF("Colour2"),
  CONF("Colour3"),
  CONF("Colour4"),
  CONF("Colour5"),
  CONF("Colour6"),
  CONF("Colour7"),
  CONF("Colour8"),
  CONF("Colour9"),
  CONF("Colour10"),
  CONF("Colour11"),
  CONF("Colour12"),
  CONF("Colour13"),
  CONF("Colour14"),
}; // pL

const TCHAR *szProfileBrush[] = {
  CONF("Brush0"),
  CONF("Brush1"),
  CONF("Brush2"),
  CONF("Brush3"),
  CONF("Brush4"),
  CONF("Brush5"),
  CONF("Brush6"),
  CONF("Brush7"),
  CONF("Brush8"),
  CONF("Brush9"),
  CONF("Brush10"),
  CONF("Brush11"),
  CONF("Brush12"),
  CONF("Brush13"),
  CONF("Brush14"),
}; // pL

const TCHAR *szProfileAirspaceMode[] = {
  CONF("AirspaceMode0"),
  CONF("AirspaceMode1"),
  CONF("AirspaceMode2"),
  CONF("AirspaceMode3"),
  CONF("AirspaceMode4"),
  CONF("AirspaceMode5"),
  CONF("AirspaceMode6"),
  CONF("AirspaceMode7"),
  CONF("AirspaceMode8"),
  CONF("AirspaceMode9"),
  CONF("AirspaceMode10"),
  CONF("AirspaceMode11"),
  CONF("AirspaceMode12"),
  CONF("AirspaceMode13"),
  CONF("AirspaceMode14"),
}; // pL

const TCHAR *szProfileAirspacePriority[] = {
  CONF("AirspacePriority0"),
  CONF("AirspacePriority1"),
  CONF("AirspacePriority2"),
  CONF("AirspacePriority3"),
  CONF("AirspacePriority4"),
  CONF("AirspacePriority5"),
  CONF("AirspacePriority6"),
  CONF("AirspacePriority7"),
  CONF("AirspacePriority8"),
  CONF("AirspacePriority9"),
  CONF("AirspacePriority10"),
  CONF("AirspacePriority11"),
  CONF("AirspacePriority12"),
  CONF("AirspacePriority13"),
  CONF("AirspacePriority14"),
}; // pL

const TCHAR szProfileAirspaceWarning[] = CONF("AirspaceWarn");
const TCHAR szProfileAirspaceBlackOutline[] = CONF("AirspaceBlackOutline");
const TCHAR szProfileAltMargin[] = CONF("AltMargin");
const TCHAR szProfileAltMode[] = CONF("AltitudeMode");
const TCHAR szProfileAltitudeUnitsValue[] = CONF("Altitude");
const TCHAR szProfileCircleZoom[] = CONF("CircleZoom");
const TCHAR szProfileClipAlt[] = CONF("ClipAlt");
const TCHAR szProfileDisplayText[] = CONF("DisplayText");
const TCHAR szProfileDisplayUpValue[] = CONF("DisplayUp");
const TCHAR szProfileDistanceUnitsValue[] = CONF("Distance");
const TCHAR szProfileDrawTerrain[] = CONF("DrawTerrain");
const TCHAR szProfileDrawTopology[] = CONF("DrawTopology");
const TCHAR szProfileFAISector[] = CONF("FAISector");
const TCHAR szProfileFinalGlideTerrain[] = CONF("FinalGlideTerrain");
const TCHAR szProfileAutoWind[] = CONF("AutoWind");
const TCHAR szProfileHomeWaypoint[] = CONF("HomeWaypoint");
const TCHAR szProfileAlternate1[] = CONF("Alternate1"); // VENTA3
const TCHAR szProfileAlternate2[] = CONF("Alternate2");
const TCHAR szProfileLiftUnitsValue[] = CONF("Lift");
const TCHAR szProfileLatLonUnits[] = CONF("LatLonUnits");
const TCHAR szProfilePolarID[] = CONF("Polar"); // pL
const TCHAR szProfileRegKey[] = CONF("RegKey");
const TCHAR szProfileSafetyAltitudeArrival[] = CONF("SafetyAltitudeArrival");
const TCHAR szProfileSafetyAltitudeBreakOff[] = CONF("SafetyAltitudeBreakOff");
const TCHAR szProfileSafetyAltitudeTerrain[] = CONF("SafetyAltitudeTerrain");
const TCHAR szProfileSafteySpeed[] = CONF("SafteySpeed");
const TCHAR szProfileSectorRadius[] = CONF("Radius");
const TCHAR szProfileSnailTrail[] = CONF("SnailTrail");
const TCHAR szProfileTrailDrift[] = CONF("TrailDrift");
const TCHAR szProfileThermalLocator[] = CONF("ThermalLocator");
const TCHAR szProfileAnimation[] = CONF("Animation");
const TCHAR szProfileSpeedUnitsValue[] = CONF("Speed");
const TCHAR szProfileTaskSpeedUnitsValue[] = CONF("TaskSpeed");
const TCHAR szProfileStartLine[] = CONF("StartLine");
const TCHAR szProfileStartRadius[] = CONF("StartRadius");
const TCHAR szProfileFinishLine[] = CONF("FinishLine");
const TCHAR szProfileFinishRadius[] = CONF("FinishRadius");
const TCHAR szProfileWarningTime[] = CONF("WarnTime");
const TCHAR szProfileAcknowledgementTime[] = CONF("AcknowledgementTime");
const TCHAR szProfileWindSpeed[] = CONF("WindSpeed");
const TCHAR szProfileWindBearing[] = CONF("WindBearing");
const TCHAR szProfileAirfieldFile[] = CONF("AirfieldFile"); // pL
const TCHAR szProfileAirspaceFile[] = CONF("AirspaceFile"); // pL
const TCHAR szProfileAdditionalAirspaceFile[] = CONF("AdditionalAirspaceFile"); // pL
const TCHAR szProfilePolarFile[] = CONF("PolarFile"); // pL
const TCHAR szProfileTerrainFile[] = CONF("TerrainFile"); // pL
const TCHAR szProfileTopologyFile[] = CONF("TopologyFile"); // pL
const TCHAR szProfileWayPointFile[] = CONF("WPFile"); // pL
const TCHAR szProfileAdditionalWayPointFile[] = CONF("AdditionalWPFile"); // pL
const TCHAR szProfileLanguageFile[] = CONF("LanguageFile"); // pL
const TCHAR szProfileStatusFile[] = CONF("StatusFile"); // pL
const TCHAR szProfileInputFile[] = CONF("InputFile"); // pL
const TCHAR szProfilePilotName[] = CONF("PilotName");
const TCHAR szProfileAircraftType[] = CONF("AircraftType");
const TCHAR szProfileAircraftRego[] = CONF("AircraftRego");
const TCHAR szProfileLoggerID[] = CONF("LoggerID");
const TCHAR szProfileLoggerShort[] = CONF("LoggerShortName");
const TCHAR szProfileSoundVolume[] = CONF("SoundVolume");
const TCHAR szProfileSoundDeadband[] = CONF("SoundDeadband");
const TCHAR szProfileSoundAudioVario[] = CONF("AudioVario");
const TCHAR szProfileSoundTask[] = CONF("SoundTask");
const TCHAR szProfileSoundModes[] = CONF("SoundModes");
const TCHAR szProfileNettoSpeed[] = CONF("NettoSpeed");
const TCHAR szProfileAccelerometerZero[] = CONF("AccelerometerZero");
const TCHAR szProfileCDICruise[] = CONF("CDICruise");
const TCHAR szProfileCDICircling[] = CONF("CDICircling");

const TCHAR szProfileAutoBlank[] = CONF("AutoBlank");
const TCHAR szProfileAutoBacklight[] = CONF("AutoBacklight");
const TCHAR szProfileAutoSoundVolume[] = CONF("AutoSoundVolume");
const TCHAR szProfileExtendedVisualGlide[] = CONF("ExtVisualGlide");
const TCHAR szProfileVirtualKeys[] = CONF("VirtualKeys");
const TCHAR szProfileAverEffTime[] = CONF("AverEffTime");
const TCHAR szProfileVarioGauge[] = CONF("VarioGauge");

const TCHAR szProfileDebounceTimeout[] = CONF("DebounceTimeout");

const TCHAR szProfileAppIndFinalGlide[] = CONF("AppIndFinalGlide");
const TCHAR szProfileAppIndLandable[] = CONF("AppIndLandable");
const TCHAR szProfileAppInverseInfoBox[] = CONF("AppInverseInfoBox");
const TCHAR szProfileAppGaugeVarioSpeedToFly[] = CONF("AppGaugeVarioSpeedToFly");
const TCHAR szProfileAppGaugeVarioAvgText[] = CONF("AppGaugeVarioAvgText");
const TCHAR szProfileAppGaugeVarioMc[] = CONF("AppGaugeVarioMc");
const TCHAR szProfileAppGaugeVarioBugs[] = CONF("AppGaugeVarioBugs");
const TCHAR szProfileAppGaugeVarioBallast[] = CONF("AppGaugeVarioBallast");
const TCHAR szProfileAppGaugeVarioGross[] = CONF("AppGaugeVarioGross");
const TCHAR szProfileAppCompassAppearance[] = CONF("AppCompassAppearance");
const TCHAR szProfileAppStatusMessageAlignment[] = CONF("AppStatusMessageAlignment");
const TCHAR szProfileAppTextInputStyle[] = CONF("AppTextInputStyle");
const TCHAR szProfileAppDialogStyle[] = CONF("AppDialogStyle");
const TCHAR szProfileAppInfoBoxColors[] = CONF("AppInfoBoxColors");
const TCHAR szProfileAppDefaultMapWidth[] = CONF("AppDefaultMapWidth");
const TCHAR szProfileTeamcodeRefWaypoint[] = CONF("TeamcodeRefWaypoint");
const TCHAR szProfileAppInfoBoxBorder[] = CONF("AppInfoBoxBorder");

#if defined(PNA) || defined(FIVV)
const TCHAR szProfileAppInfoBoxGeom[] = CONF("AppInfoBoxGeom"); // VENTA-ADDON GEOMETRY CONFIG
const TCHAR szProfileAppInfoBoxModel[] = CONF("AppInfoBoxModel"); // VENTA-ADDON MODEL CONFIG
#endif

const TCHAR szProfileAppAveNeedle[] = CONF("AppAveNeedle");

const TCHAR szProfileAutoAdvance[] = CONF("AutoAdvance");
const TCHAR szProfileUTCOffset[] = CONF("UTCOffset");
const TCHAR szProfileBlockSTF[] = CONF("BlockSpeedToFly");
const TCHAR szProfileAutoZoom[] = CONF("AutoZoom");
const TCHAR szProfileMenuTimeout[] = CONF("MenuTimeout");
const TCHAR szProfileLockSettingsInFlight[] = CONF("LockSettingsInFlight");
const TCHAR szProfileTerrainContrast[] = CONF("TerrainContrast");
const TCHAR szProfileTerrainBrightness[] = CONF("TerrainBrightness");
const TCHAR szProfileTerrainRamp[] = CONF("TerrainRamp");
const TCHAR szProfileEnableFLARMMap[] = CONF("EnableFLARMDisplay");
const TCHAR szProfileEnableFLARMGauge[] = CONF("EnableFLARMGauge");
const TCHAR szProfileFLARMGaugeBearing[] = CONF("FLARMGaugeBearing");
const TCHAR szProfileGliderScreenPosition[] = CONF("GliderScreenPosition");
const TCHAR szProfileSetSystemTimeFromGPS[] = CONF("SetSystemTimeFromGPS");

const TCHAR szProfileVoiceClimbRate[] = CONF("VoiceClimbRate");
const TCHAR szProfileVoiceTerrain[] = CONF("VoiceTerrain");
const TCHAR szProfileVoiceWaypointDistance[] = CONF("VoiceWaypointDistance");
const TCHAR szProfileVoiceTaskAltitudeDifference[] = CONF("VoiceTaskAltitudeDifference");
const TCHAR szProfileVoiceMacCready[] = CONF("VoiceMacCready");
const TCHAR szProfileVoiceNewWaypoint[] = CONF("VoiceNewWaypoint");
const TCHAR szProfileVoiceInSector[] = CONF("VoiceInSector");
const TCHAR szProfileVoiceAirspace[] = CONF("VoiceAirspace");

const TCHAR szProfileFinishMinHeight[] = CONF("FinishMinHeight");
const TCHAR szProfileStartMaxHeight[] = CONF("StartMaxHeight");
const TCHAR szProfileStartMaxSpeed[] = CONF("StartMaxSpeed");
const TCHAR szProfileStartMaxHeightMargin[] = CONF("StartMaxHeightMargin");
const TCHAR szProfileStartMaxSpeedMargin[] = CONF("StartMaxSpeedMargin");
const TCHAR szProfileStartHeightRef[] = CONF("StartHeightRef");
const TCHAR szProfileEnableNavBaroAltitude[] = CONF("EnableNavBaroAltitude");

const TCHAR szProfileLoggerTimeStepCruise[] = CONF("LoggerTimeStepCruise");
const TCHAR szProfileLoggerTimeStepCircling[] = CONF("LoggerTimeStepCircling");

const TCHAR szProfileSafetyMacCready[] = CONF("SafetyMacCready");
const TCHAR szProfileAbortSafetyUseCurrent[] = CONF("AbortSafetyUseCurrent");
const TCHAR szProfileAutoMcMode[] = CONF("AutoMcMode");
const TCHAR szProfileWaypointsOutOfRange[] = CONF("WaypointsOutOfRange");
const TCHAR szProfileEnableExternalTriggerCruise[] = CONF("EnableExternalTriggerCruise");
const TCHAR szProfileFAIFinishHeight[] = CONF("FAIFinishHeight");
const TCHAR szProfileOLCRules[] = CONF("OLCRules");
const TCHAR szProfileHandicap[] = CONF("Handicap");
const TCHAR szProfileSnailWidthScale[] = CONF("SnailWidthScale");
const TCHAR szProfileUserLevel[] = CONF("UserLevel");
const TCHAR szProfileRiskGamma[] = CONF("RiskGamma");
const TCHAR szProfileWindArrowStyle[] = CONF("WindArrowStyle");
const TCHAR szProfileDisableAutoLogger[] = CONF("DisableAutoLogger");
const TCHAR szProfileMapFile[] = CONF("MapFile"); // pL
const TCHAR szProfileBallastSecsToEmpty[] = CONF("BallastSecsToEmpty");
const TCHAR szProfileUseCustomFonts[] = CONF("UseCustomFonts");
const TCHAR szProfileFontInfoWindowFont[] = CONF("InfoWindowFont");
const TCHAR szProfileFontTitleWindowFont[] = CONF("TitleWindowFont");
const TCHAR szProfileFontMapWindowFont[] = CONF("MapWindowFont");
const TCHAR szProfileFontTitleSmallWindowFont[] = CONF("TeamCodeFont");
const TCHAR szProfileFontMapWindowBoldFont[] = CONF("MapWindowBoldFont");
const TCHAR szProfileFontCDIWindowFont[] = CONF("CDIWindowFont");
const TCHAR szProfileFontMapLabelFont[] = CONF("MapLabelFont");
const TCHAR szProfileFontStatisticsFont[] = CONF("StatisticsFont");

#ifndef WIN32

class GConf {
protected:
  GConfEngine *engine;

public:
  GConf():engine(gconf_engine_get_default()) {}
  ~GConf() {
    gconf_engine_unref(engine);
  }

  bool get(const char *key, int &value) {
    GError *error = NULL;
    value = gconf_engine_get_int(engine, key, &error);
    if (value == 0 && error != NULL) {
      g_error_free(error);
      return false;
    }

    return true;
  }

  bool get(const char *key, char *value, size_t max_length) {
    gchar *buffer = gconf_engine_get_string(engine, key, NULL);
    if (buffer == NULL)
      return false;

    g_strlcpy(value, buffer, max_length);
    g_free(buffer);
    return true;
  }

  bool set(const char *key, int value) {
    return gconf_engine_set_int(engine, key, value, NULL);
  }

  bool set(const char *key, const char *value) {
    return gconf_engine_set_string(engine, key, value, NULL);
  }
};

#endif /* !WIN32 */

void
StoreType(int Index, int the_type)
{
  SetToRegistry(szProfileDisplayType[Index], the_type);
}

void
SetRegistryStringIfAbsent(const TCHAR* name, const TCHAR* value)
{
  // VENTA force fonts registry rewrite in PNAs
#if defined(PNA) || defined(FIVV) // VENTA TODO WARNING should really delete the key before creating it TODO
  SetRegistryString(name, value);
#else
  TCHAR temp[MAX_PATH];
  if (GetRegistryString(name, temp, MAX_PATH))
    SetRegistryString(name, value);
#endif
}

//
// NOTE: all registry variables are unsigned!
//
bool
GetFromRegistryD(const TCHAR *szRegValue, DWORD &pPos)
{
// returns 0 on SUCCESS, else the non-zero error code
#ifdef WIN32

  HKEY hKey;
  DWORD dwSize, dwType;
  long hRes;
  DWORD defaultVal;

  hRes = RegOpenKeyEx(HKEY_CURRENT_USER, szProfileKey, 0, KEY_ALL_ACCESS, &hKey);
  if (hRes != ERROR_SUCCESS)
    return hRes;

  defaultVal = pPos;
  dwSize = sizeof(DWORD);
  hRes = RegQueryValueEx(hKey, szRegValue, 0, &dwType, (LPBYTE) & pPos, &dwSize);
  if (hRes != ERROR_SUCCESS)
    pPos = defaultVal;

  RegCloseKey(hKey);
  return hRes;

#else /* !WIN32 */

  int value;
  if (!GConf().get(szRegValue, value))
    return false;

  pPos = (DWORD)value;
  return true;

#endif /* !WIN32 */
}

bool
GetFromRegistry(const TCHAR *szRegValue, int &pPos)
{
  DWORD Temp = pPos;
  long res;
  if ((res = GetFromRegistryD(szRegValue, Temp)) == ERROR_SUCCESS)
    pPos = Temp;

  return res;
}

bool
GetFromRegistry(const TCHAR *szRegValue, short &pPos)
{
  DWORD Temp = pPos;
  long res;
  if ((res = GetFromRegistryD(szRegValue, Temp)) == ERROR_SUCCESS)
    pPos = Temp;

  return res;
}

bool
GetFromRegistry(const TCHAR *szRegValue, bool &pPos)
{
  DWORD Temp = pPos;
  long res;
  if ((res = GetFromRegistryD(szRegValue, Temp)) == ERROR_SUCCESS)
    pPos = Temp > 0;

  return res;
}

bool
GetFromRegistry(const TCHAR *szRegValue, unsigned &pPos)
{
  DWORD Temp = pPos;
  long res;
  if ((res = GetFromRegistryD(szRegValue, Temp)) == ERROR_SUCCESS)
    pPos = Temp;

  return res;
}

bool
GetFromRegistry(const TCHAR *szRegValue, double &pPos)
{
  DWORD Temp = (DWORD)pPos;
  long res;
  if ((res = GetFromRegistryD(szRegValue, Temp)) == ERROR_SUCCESS)
    pPos = (double)Temp;

  return res;
}

HRESULT
SetToRegistry(const TCHAR *szRegValue, DWORD Pos)
{
#ifdef WIN32

  HKEY hKey;
  DWORD Disp;
  HRESULT hRes;

  hRes = RegCreateKeyEx(HKEY_CURRENT_USER, szProfileKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &Disp);
  if (hRes != ERROR_SUCCESS)
    return FALSE;

  hRes = RegSetValueEx(hKey, szRegValue, 0, REG_DWORD, (LPBYTE)&Pos,
                       sizeof(DWORD));
  RegCloseKey(hKey);

  return hRes;

#else /* !WIN32 */

  GConf().set(szRegValue, (int)Pos);
  return 0;

#endif /* !WIN32 */
}

// Set bool value to registry as 1 or 0
HRESULT
SetToRegistry(const TCHAR *szRegValue, bool bVal)
{
  return SetToRegistry(szRegValue, bVal ? DWORD(1) : DWORD(0));
}

// Set int value to registry
HRESULT
SetToRegistry(const TCHAR *szRegValue, int nVal)
{
  return SetToRegistry(szRegValue, DWORD(nVal));
}

#ifndef HAVE_POSIX /* DWORD==unsigned on WINE, would be duplicate */
HRESULT
SetToRegistry(const TCHAR *szRegValue, unsigned nVal)
{
  return SetToRegistry(szRegValue, DWORD(nVal));
}
#endif

/**
 * Reads a value from the registry file
 * @param szRegValue Name of the value that should be read
 * @param pPos Pointer to the output buffer
 * @param dwSize Maximum size of the output buffer
 */
bool
GetRegistryString(const TCHAR *szRegValue, TCHAR *pPos, DWORD dwSize)
{
#ifdef WIN32

  HKEY hKey;
  DWORD dwType = REG_SZ;
  long hRes;
  unsigned int i;
  for (i = 0; i < dwSize; i++) {
    pPos[i] = 0;
  }

  pPos[0]= '\0';
  hRes = RegOpenKeyEx(HKEY_CURRENT_USER, szProfileKey, 0,
                      KEY_READ, &hKey);
  if (hRes != ERROR_SUCCESS)
    return false;

  dwSize *= sizeof(pPos[0]);

  hRes = RegQueryValueEx(hKey, szRegValue, 0, &dwType, (LPBYTE)pPos, &dwSize);

  RegCloseKey(hKey);
  return hRes == ERROR_SUCCESS;

#else /* !WIN32 */
  return GConf().get(szRegValue, pPos, dwSize);
#endif /* !WIN32 */
}

/**
 * Writes a value to the registry
 * @param szRegValue Name of the value that should be written
 * @param Pos Value that should be written
 */
bool
SetRegistryString(const TCHAR *szRegValue, const TCHAR *Pos)
{
#ifdef WIN32

  HKEY    hKey;
  DWORD    Disp;
  HRESULT hRes;

  hRes = RegCreateKeyEx(HKEY_CURRENT_USER, szProfileKey, 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hKey, &Disp);
  if (hRes != ERROR_SUCCESS)
    return false;

  hRes = RegSetValueEx(hKey, szRegValue, 0, REG_SZ, (LPBYTE)Pos,
                       (_tcslen(Pos) + 1) * sizeof(TCHAR));
  RegCloseKey(hKey);

  return hRes == ERROR_SUCCESS;

#else /* !WIN32 */
  return GConf().set(szRegValue, Pos);
#endif /* !WIN32 */
}

#define CheckIndex(x, i) assert(i >= 0 && (unsigned)i < sizeof(x) / sizeof(x[0]))

void
SetRegistryColour(int i, int c)
{
  CheckIndex(szProfileColour, i);
  SetToRegistry(szProfileColour[i], c);
}

void
SetRegistryBrush(int i, int c)
{
  CheckIndex(szProfileBrush, i);
  SetToRegistry(szProfileBrush[i], c);
}

const TCHAR *
MakeDeviceSettingName(TCHAR *buffer, const TCHAR *prefix, unsigned n,
                      const TCHAR *suffix)
{
  _tcscpy(buffer, prefix);

  if (n > 0)
    _stprintf(buffer + _tcslen(buffer), _T("%u"), n + 1);

  _tcscat(buffer, suffix);

  return buffer;
}

static enum DeviceConfig::port_type
StringToPortType(const TCHAR *value)
{
  if (_tcscmp(value, _T("serial")) == 0)
    return DeviceConfig::SERIAL;

  if (_tcscmp(value, _T("auto")) == 0)
    return DeviceConfig::AUTO;

  return DeviceConfig::SERIAL;
}

static enum DeviceConfig::port_type
ReadPortType(unsigned n)
{
  TCHAR name[64], value[64];

  MakeDeviceSettingName(name, CONF("Port"), n, _T("Type"));
  if (!GetRegistryString(name, value, sizeof(value) / sizeof(value[0])))
    return DeviceConfig::SERIAL;

  return StringToPortType(value);
}

void
ReadDeviceConfig(unsigned n, DeviceConfig &config)
{
  TCHAR buffer[64];
  unsigned Temp = 0;

  config.port_type = ReadPortType(n);

  MakeDeviceSettingName(buffer, CONF("Port"), n, _T("Index"));
  if (GetFromRegistry(buffer, Temp) == ERROR_SUCCESS)
    config.port_index = Temp;

  MakeDeviceSettingName(buffer, CONF("Speed"), n, _T("Index"));
  if (GetFromRegistry(buffer, Temp) == ERROR_SUCCESS)
    config.speed_index = Temp;

  config.driver_name[0] = '\0';

  _tcscpy(buffer, CONF("DeviceA"));
  buffer[_tcslen(buffer) - 1] += n;
  GetRegistryString(buffer, config.driver_name,
                    sizeof(config.driver_name) / sizeof(config.driver_name[0]));
}

static const TCHAR *
PortTypeToString(enum DeviceConfig::port_type type)
{
  switch (type) {
  case DeviceConfig::SERIAL:
    return _T("serial");

  case DeviceConfig::AUTO:
    return _T("auto");
  }

  return NULL;
}

static bool
WritePortType(unsigned n, enum DeviceConfig::port_type type)
{
  const TCHAR *value = PortTypeToString(type);
  if (value == NULL)
    return false;

  TCHAR name[64];

  MakeDeviceSettingName(name, CONF("Port"), n, _T("Type"));
  return SetRegistryString(name, value) == ERROR_SUCCESS;
}

void
WriteDeviceConfig(unsigned n, const DeviceConfig &config)
{
  TCHAR buffer[64];

  WritePortType(n, config.port_type);

  MakeDeviceSettingName(buffer, CONF("Port"), n, _T("Index"));
  SetToRegistry(buffer, config.port_index);

  MakeDeviceSettingName(buffer, CONF("Speed"), n, _T("Index"));
  SetToRegistry(buffer, config.speed_index);

  _tcscpy(buffer, CONF("DeviceA"));
  buffer[_tcslen(buffer) - 1] += n;
  SetRegistryString(buffer, config.driver_name);
}

// Registry file handling

const static size_t nMaxValueNameSize = MAX_PATH + 6; //255 + 1 + /r/n
const static size_t nMaxValueValueSize = MAX_PATH * 2 + 6; // max regkey name is 256 chars + " = "
const static size_t nMaxClassSize = MAX_PATH + 6;
const static size_t nMaxKeyNameSize = MAX_PATH + 6;

static bool
LoadRegistryFromFile_inner(const TCHAR *szFile, bool wide = true)
{
  LogStartUp(TEXT("Loading registry from %s"), szFile);
  bool found = false;
  FILE *fp = NULL;
  if (!string_is_empty(szFile))
#ifndef __GNUC__
    if (wide)
      fp = _tfopen(szFile, TEXT("rb"));
    else
      fp = _tfopen(szFile, TEXT("rt"));
#else
  fp = _tfopen(szFile, TEXT("rb")); //20060515:sgi add b
#endif
  if (fp == NULL)
    // error
    return false;

  TCHAR winval[nMaxValueValueSize];
  TCHAR wname[nMaxValueValueSize];
  TCHAR wvalue[nMaxValueValueSize];
  int j;

#ifdef __GNUC__
  char inval[nMaxValueValueSize];
  char name [nMaxValueValueSize];
  char value [nMaxValueValueSize];

  if (wide) {
#endif

  while (_fgetts(winval, nMaxValueValueSize, fp)) {

#ifdef _UNICODE
    if (winval[0] > 255)
      // not reading corectly, probably narrow file.
      break;
#endif /* _UNICODE */

    if (_stscanf(winval, TEXT("%[^#=\r\n ]=\"%[^\r\n\"]\"[\r\n]"),
                 wname, wvalue) == 2) {
      if (!string_is_empty(wname)) {
        SetRegistryString(wname, wvalue);
        found = true;
      }
    } else if (_stscanf(winval, TEXT("%[^#=\r\n ]=%d[\r\n]"), wname, &j) == 2) {
      if (!string_is_empty(wname)) {
        SetToRegistry(wname, j);
        found = true;
      }
    } else if (_stscanf(winval, TEXT("%[^#=\r\n ]=\"\"[\r\n]"), wname) == 1) {
      if (!string_is_empty(wname)) {
        SetRegistryString(wname, TEXT(""));
        found = true;
      }
    } else {
      // assert(false);	// Invalid line reached
    }
  }

#ifdef __GNUC__
  } else {
  while (fgets(inval, nMaxValueValueSize, fp)) {
    if (sscanf(inval, "%[^#=\r\n ]=\"%[^\r\n\"]\"[\r\n]", name, value) == 2) {
      if (strlen(name)>0) {
#ifdef _UNICODE
        mbstowcs(wname, name, strlen(name)+1);
        mbstowcs(wvalue, value, strlen(value)+1);
#else
        strcpy(wname, name);
        strcpy(wvalue, value);
#endif
        SetRegistryString(wname, wvalue);
        found = true;
      }
    } else if (sscanf(inval, "%[^#=\r\n ]=%d[\r\n]", name, &j) == 2) {
      if (strlen(name)>0) {
#ifdef _UNICODE
        mbstowcs(wname, name, strlen(name)+1);
#else
        strcpy(wname, name);
#endif
        SetToRegistry(wname, j);
        found = true;
      }
    } else if (sscanf(inval, "%[^#=\r\n ]=\"\"[\r\n]", name) == 1) {
      if (strlen(name)>0) {
#ifdef _UNICODE
        mbstowcs(wname, name, strlen(name)+1);
#else
        strcpy(wname, name);
#endif
        SetRegistryString(wname, TEXT(""));
        found = true;
      }
    } else {
      // assert(false);	// Invalid line reached
    }
  }
}
#endif

  fclose(fp);

  return found;
}

void
LoadRegistryFromFile(const TCHAR *szFile)
{
#ifndef __GNUC__
  // legacy, wide chars
  if (!LoadRegistryFromFile_inner(szFile,true))
    // new, non-wide chars
    LoadRegistryFromFile_inner(szFile,false);
#else
  // new, non-wide chars
  if (!LoadRegistryFromFile_inner(szFile,false))
    // legacy, wide chars
    LoadRegistryFromFile_inner(szFile,true);
#endif
}

void
SaveRegistryToFile(const TCHAR *szFile)
{
#ifdef WIN32
  TCHAR lpstrName[nMaxKeyNameSize+1];
  //  TCHAR lpstrClass[nMaxClassSize+1];
#ifdef __GNUC__
  union {
    BYTE pValue[nMaxValueValueSize+4];
    DWORD dValue;
  } uValue;
#else
  BYTE pValue[nMaxValueValueSize+1];

  char sName[MAX_PATH];
  char sValue[MAX_PATH];

#endif

  HKEY hkFrom;
  LONG res = ::RegOpenKeyEx(HKEY_CURRENT_USER, szProfileKey,
                            0, KEY_ALL_ACCESS, &hkFrom);

  if (ERROR_SUCCESS != res)
    return;

  FILE *fp = NULL;
  if (!string_is_empty(szFile))
    fp = _tfopen(szFile, TEXT("wb"));
  if(fp == NULL) {
    // error
    ::RegCloseKey(hkFrom);
    return;
  }

  for (int i = 0;; i++) {
    DWORD nType;
    DWORD nValueSize = nMaxValueValueSize;
    DWORD nNameSize = nMaxKeyNameSize;
    // DWORD nClassSize = nMaxClassSize;

    lpstrName[0] = _T('\0'); // null terminate, just in case

    LONG res = ::RegEnumValue(hkFrom, i, lpstrName,
                              &nNameSize, 0,
#ifdef __GNUC__
                              &nType, uValue.pValue,
#else
                              &nType, pValue,
#endif
                              &nValueSize);

    if (ERROR_NO_MORE_ITEMS == res)
      break;

    if ((nNameSize <= 0) || (nNameSize > nMaxKeyNameSize))
      // in case things get weird
      continue;

    // null terminate, just in case
    lpstrName[nNameSize] = _T('\0');

    if (_tcslen(lpstrName) > 1) {
      // type 1 text
      // type 4 integer (valuesize 4)

      if (nType == 4) { // data
#ifdef __GNUC__
        fprintf(fp, "%S=%d\r\n", lpstrName, uValue.dValue);
#else
        wcstombs(sName, lpstrName, nMaxKeyNameSize + 1);
        fprintf(fp, "%s=%d\r\n", sName, *((DWORD*)pValue));
#endif
      } else if (nType == 1) {
        // text
        // XXX SCOTT - Check that the output data (lpstrName and pValue) do not contain \r or \n
        if (nValueSize > 0) {
#ifdef __GNUC__
          uValue.pValue[nValueSize] = 0; // null terminate, just in case
          uValue.pValue[nValueSize + 1] = 0; // null terminate, just in case
          if (!string_is_empty((const TCHAR*)uValue.pValue))
            fprintf(fp, "%S=\"%S\"\r\n", lpstrName, uValue.pValue);
          else
            fprintf(fp, "%S=\"\"\r\n", lpstrName);
#else
          if (!string_is_empty((const TCHAR*)pValue)) {
            pValue[nValueSize] = 0; // null terminate, just in case
            pValue[nValueSize + 1] = 0; // null terminate, just in case
            wcstombs(sName, lpstrName, nMaxKeyNameSize + 1);
            wcstombs(sValue, (TCHAR*)pValue, nMaxKeyNameSize + 1);
            fprintf(fp, "%s=\"%s\"\r\n", sName, sValue);
          } else {
            wcstombs(sName, lpstrName, nMaxKeyNameSize + 1);
            fprintf(fp, "%s=\"\"\r\n", sName);
          }
#endif
        } else {
#ifdef __GNUC__
          fprintf(fp, "%S=\"\"\r\n", lpstrName);
#else
          fprintf(fp, "%s=\"\"\r\n", lpstrName);
#endif
        }
      }
    }
  }
#ifdef __GNUC__
  // JMW why flush agressively?
  fflush(fp);
#endif

#ifdef __GNUC__
  fprintf(fp, "\r\n"); // end of file
#endif

  fclose(fp);

  ::RegCloseKey(hkFrom);
#else /* !WIN32 */
  // XXX implement
#endif /* !WIN32 */
}
