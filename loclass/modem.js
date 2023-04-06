<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="Pragma" content="no-cache" />
<meta http-equiv="X-UA-Compatible" content="IE=edge;chrome=1"><!-IE7 mode->
<script language="JavaScript" src="../../../resource/common/util.js?2019053005314313-2068654386"></script>
<script language="JavaScript" src="../../../resource/spanish/ssmpdes.js?2019053005314313-2068654386"></script>
<script language="JavaScript" src='../../../Cusjs/InitFormCus.js?2019053005314313-2068654386'></script>
<script language="JavaScript" src="../../../resource/common/InitForm.asp?2019053005314313-2068654386"></script>
<link rel="stylesheet"  href='../../../resource/common/style.css?2019053005314313-2068654386' type='text/css'>
<link rel="stylesheet"  href='../../../Cuscss/spanish/frame.css?2019053005314313-2068654386' type='text/css'>
<script language="JavaScript" src="../../../resource/spanish/ampdes.html?2019053005314313-2068654386"></script>
<style type="text/css">
.width_66per {
    width: 66%;
}
</style>
<script language="JavaScript" src="deviceinfo.cus?2019053005314313-2068654386"></script>
<script language="JavaScript" type="text/javascript">
var curLanguage='spanish';
function stDeviceInfo(domain,SerialNumber,HardwareVersion,SoftwareVersion,ModelName,VendorID,ReleaseTime,Mac,Description,ManufactureInfo,DeviceAlias)
{
    this.domain                = domain;
    this.SerialNumber          = SerialNumber;
    this.HardwareVersion       = HardwareVersion;
    this.SoftwareVersion       = SoftwareVersion;
    this.ModelName             = ModelName;
    this.VendorID              = VendorID;
    this.ReleaseTime           = ReleaseTime;
    this.Mac                   = Mac;
    this.Description           = Description;
    this.ManufactureInfo       = ManufactureInfo;
    this.DeviceAlias           = DeviceAlias;
}

function ONTInfo(domain,ONTID,Status)
{
    this.domain = domain;
    this.ONTID  = ONTID;
    this.Status = Status;
}

function isFirst8VisibleChar(sn)
{
    if (
        ((sn.charAt(0) >= '2')&&(sn.charAt(0) <= '7'))
        &&((sn.charAt(2) >= '2')&&(sn.charAt(2) <= '7'))
        &&((sn.charAt(4) >= '2')&&(sn.charAt(4) <= '7'))
        &&((sn.charAt(6) >= '2')&&(sn.charAt(6) <= '7'))
       )
    {
        if (
            ((sn.charAt(0) == '7')&&(sn.charAt(1) == 'F'))
            ||((sn.charAt(2) == '7')&&(sn.charAt(3) == 'F'))
            ||((sn.charAt(4) == '7')&&(sn.charAt(5) == 'F'))
            ||((sn.charAt(6) == '7')&&(sn.charAt(7) == 'F'))
           )
        {
            return false;
        }
        return true;
    }
    return false;
}

function getMinus(a)
{
    if ( a > '9' )
    {
        if ( (a >= 'A') && (a <= 'F') )
        {
            return 55;
        }
        else
        {
            return 87;
        }
    }
    else
    {
        return 48;
    }
}

function conv16to12Sn(SerialNum)
{
    var charVid = "";
    var hexVid = "";
    var vssd = "";
    var i;

    hexVid = SerialNum.substr(0,8);
    vssd = SerialNum.substr(8,12);

    for(i=0; i<8; i+=2)
    {
        charVid += String.fromCharCode("0x"+hexVid.substr(i, 2));
    }

    return charVid+vssd;
}

var ontMatchOLTStatus = '0';
var ONTUserServices =  '';
var ontInfos = new Array(new ONTInfo("InternetGatewayDevice.X_HW_DEBUG.AMP.ONT","5","O5"),null);
var ontEPONInfos = new Array(null);
var ontPonMode = 'gpon';
var deviceInfos = new Array(new stDeviceInfo("InternetGatewayDevice.DeviceInfo","485754435CAD44A5","15ADA","V5R019C10S110A","HG8145V5","HWTC","2019\x2d05\x2d30\x5f05\x3a31\x3a43\x20","C4\x3aA4\x3a02\x3a55\x3aBE\x3a8A","EchoLife\x20HG8145V5\x20GPON\x20Terminal\x20\x28CLASS\x20B\x2b\x2fPRODUCT\x20ID\x3a2150083933AGM2005738\x2fCHIP\x3a000b0020210107\x29","2150083933AGM2005738\x2eC412",""),null);
var ontInfo = ontInfos[0];
var ontEPONInfo = ontEPONInfos[0];
var deviceInfo = deviceInfos[0];

var showCPUnMemUsed = '1';
var cpuUsed = '17%';
var memUsed = '41%';
var MngtPccw = '0';
var MngtTelmex = '1';
var var_singtel = '0';
var CfgMode ='TELMEX5GV5';
var IsDefaultPwd = '1';
var IsModifiedPwd = '0';
var customizeDes = 'TELMEX\x28TR181\x29';
var SN = deviceInfo.SerialNumber;
var sn = deviceInfo.SerialNumber;
var devAlias = deviceInfo.DeviceAlias;
var deviceTag = "";
var minus = 0;
var temp1 = 0;
var temp2 = 0;
var ParentalFlag = '1';
var systemdsttime = '2023-04-05 20:09:17-06:00 DST';
var opticInfo = '\x2d28\x2e24'; 
var ontPonpwd = '75356877514153517542'; 
var sysUserType = '0';
var curUserType = '0';
var ProductType = '1';
var TalkTalkFlag = '0';
var DoubleFreqFlag = '1';
var BaseInstFacKeyChgF = '0,0';
var IsPtVdf = "0";
var IsPtVdfAP = "0";
var IsPtVdfb = "0";
var BaseInstFacKeyChgF2g = BaseInstFacKeyChgF.split(',')[0];
var BaseInstFacKeyChgF5g = BaseInstFacKeyChgF.split(',')[1];
 
if (ProductType == '2')
{
    var dev_uptime = '8430';
}
else if (CfgMode.toUpperCase() == 'TELECENTRO')
{
    var dev_uptime = '8430';
}
else
{
    var dev_uptime = '8430';
}

function IsOpticalNomal()
{
    return opticInfo != "--";
}

function ParseSystemTime(SystemTime)
{
    if(SystemTime == "")
    {
      SystemTime = "1970-01-01 01:01";
    }
    document.getElementById('td14_2').innerHTML = htmlencode(SystemTime);
}

if (isFirst8VisibleChar(sn) == true)
{
    SN = deviceInfo.SerialNumber + ' ' + '(' + conv16to12Sn(deviceInfo.SerialNumber) + ')';
}

function SetUptime()
{

    dev_uptime++;
    var second = parseInt(dev_uptime);
    var dd = parseInt(second/(3600*24));
    var hh = parseInt((second%(3600*24))/3600);
    var mm = parseInt((second%3600)/60);
    var ss = parseInt(second%60);
    var strtime = "";

    if (dd <= 1)
    {
        strtime += dd + GetLanguageDesc("s020f");
    }
    else
    {
        strtime += dd + GetLanguageDesc("s0213");
    }

    if (hh <= 1)
    {
        strtime += hh + GetLanguageDesc("s0210");
    }
    else
    {
        strtime += hh + GetLanguageDesc("s0214");
    }

    if (mm <= 1)
    {
        strtime += mm + GetLanguageDesc("s0211");
    }
    else
    {
        strtime += mm + GetLanguageDesc("s0215");
    }

    if (ss <= 1)
    {
        strtime += ss + GetLanguageDesc("s0212");
    }
    else
    {
        strtime += ss + GetLanguageDesc("s0216");
    }
    getElById("ShowTime").innerHTML = htmlencode(strtime);
}

function LoadFrame()
{
    if (ProductType == '2')
    {
        document.getElementById('td6_2Row').style.display="none";
        document.getElementById('td8_2Row').style.display="none";
        document.getElementById('td14_2Row').style.display="none";

        if ( showCPUnMemUsed != 1)
        {
            document.getElementById('td9_2Row').style.display="none";
            document.getElementById('td10_2Row').style.display="none";
        }

        document.getElementById('td11_2Row').style.display="none";

        SetUptime();
        setInterval("SetUptime();", 1000);

        if((MngtTelmex != 1)||(curUserType == sysUserType))
        {
            if(IsModifiedPwd == 0 && curLanguage.toUpperCase() != 'CHINESE')
            {
                document.getElementById('DefaultNotice').style.display="";
            }
        }    
    }
    else
    {
        if (ontPonMode.toUpperCase() == 'WIFI' || ontPonMode.toUpperCase() == 'GE' || CfgMode.toUpperCase() == 'IPONLY' 
            || CfgMode.toUpperCase() == 'FORANET' || CfgMode.toUpperCase() == 'TDC' || CfgMode.toUpperCase() == 'TELIA')
        {

            document.getElementById('td7_2Row').style.display="none";
            document.getElementById('td8_2Row').style.display="none";
        }
    
        if ((CfgMode.toUpperCase() == 'TELMEXACCESS') || (CfgMode.toUpperCase() == 'TELMEXACCESSNV') || (CfgMode.toUpperCase() == 'TELMEXRESALE')
            || (CfgMode.toUpperCase() == 'IPONLY') || (CfgMode.toUpperCase() == 'FORANET') 
            || (CfgMode.toUpperCase() == 'TDC') || (CfgMode.toUpperCase() == 'TELIA'))
        {
            document.getElementById('td13_2Row').style.display="none";
        }
    
        if ( showCPUnMemUsed != 1
            || (MngtPccw == 1) )
        {
            document.getElementById('td9_2Row').style.display="none";
            document.getElementById('td10_2Row').style.display="none";
        }

        if ( MngtPccw != 1 )
        {
            document.getElementById('td11_2Row').style.display="none";
        }

        if(ontPonMode.toUpperCase() == 'EPON')
        {
            document.getElementById('td8_2Row').style.display="none";
        }

        if ((MngtTelmex != 1) && (CfgMode.toUpperCase() != 'TELECENTRO'))
        {
            document.getElementById('ShowTimeRow').style.display="none";
        }
        else
        {
            SetUptime();
            document.getElementById('td3_2').innerHTML=htmlencode(conv16to12Sn(deviceInfo.SerialNumber).toUpperCase());
            setInterval("SetUptime();", 1000);
        }
        if(IsDefaultPwd == 1 && curLanguage.toUpperCase() != 'CHINESE')
        {
            if ((CfgMode.toUpperCase() != 'TDE') && (CfgMode.toUpperCase() != 'TDEVRGW') && (false == var_singtel))
            {
                document.getElementById('DefaultNotice').style.display="";
            }
        }

        if (CfgMode.toUpperCase() == 'TEDATA2' || CfgMode.toUpperCase() == 'TEDATA')
        {
            document.getElementById('td5_2Row').style.display="none";
        }
        if (IsDefaultPwd == 1 && ('CTM' == CfgMode.toUpperCase()))
        {
            document.getElementById('DefaultNotice').style.display="";
        }
        if (CfgMode.toUpperCase()  == 'BJUNICOM')
        {
            //±±¾©jͨтѨȳ£¬ДʾCPU¡¢Ś´瑅Ϣ¡¢ՋӪʌхϢ
            //document.getElementById('td9_2Row').style.display="none";
            //document.getElementById('td10_2Row').style.display="none";
            document.getElementById('td16_2').innerHTML = DevInfoDes['s0228'];
        }
        else
        {
            document.getElementById('td15_2Row').style.display="none";
            document.getElementById('td16_2Row').style.display="none";
        }
    }
    
    var all = document.getElementsByTagName("td");
    for (var i = 0; i < all.length; i++)
    {
        var b = all[i];
        var c = b.getAttribute("BindText");
        if(c == null)
        {
            continue;
        }
        b.innerHTML = DevInfoDes[c];
    }

    if (ParentalFlag==1)
    {
        document.getElementById('td14_2Row').style.display="";
    }
    else
    {
        document.getElementById('td14_2Row').style.display="none";
    }
    if (TalkTalkFlag == 1)
    {
        var systime,splitdata,splittime,detildate,detiltime;
        systime = systemdsttime.split(" ");
        detildate = systime[0];
        detiltime = systime[1];
        splitdata = detildate.split("-");
        splittime = detiltime.split("+");
        systemdsttime = splittime[0] + " " + splitdata[2] + "/" + splitdata[1] + "/" + splitdata[0];
    }
    ParseSystemTime(systemdsttime);
    setText("DevAlias", devAlias);
    if(CfgMode.toUpperCase()=="TALKTALK2WIFI")
    {
        document.getElementById('DefaultNotice').style.display="none";
    }
    if (1 == MngtTelmex && top.countNum == 0 )
    {
        var timeout = 500;    
        var TimerHandle = setTimeout("Alertwlancfg()", timeout);
    }
if (IsPtVdf == 1 || IsPtVdfAP == 1 || IsPtVdfb == 1 )
{
   document.getElementById('devicealias').style.display="none";
}
if (((CfgMode.toUpperCase()=="TELECOM2") || (CfgMode.toUpperCase()=="TELECOM")) && (curUserType != sysUserType))
{
document.getElementById('DevAlias').disabled=true;
document.getElementById('apply').style.display="none";
}
}
function Alertwlancfg()
{
    top.countNum = 1;
    if (1 == DoubleFreqFlag)
    {
        if ((0 == BaseInstFacKeyChgF2g) && (0 == BaseInstFacKeyChgF5g))
        {
            AlertEx(cfg_wlancfgbasic_language['amp_wlan_pwd_need_change']);   
        }
        else if ((0 == BaseInstFacKeyChgF2g) && (1 == BaseInstFacKeyChgF5g))
        {
            AlertEx(cfg_wlancfgbasic_language['amp_wlan_pwd_need_change_2G']); 
        }
        else if ((1 == BaseInstFacKeyChgF2g) && (0 == BaseInstFacKeyChgF5g))
        {
              AlertEx(cfg_wlancfgbasic_language['amp_wlan_pwd_need_change_5G']); 
        }
    }
    else
    {
        if (0 == BaseInstFacKeyChgF2g)
        {
              AlertEx(cfg_wlancfgbasic_language['amp_wlan_pwd_need_change']);   
        }    
    }
}

function GetLanguageDesc(Name)
{
    return DevInfoDes[Name];
}

function GetONTRegisterStatus()
{
    if (ontMatchOLTStatus == '1' && IsOpticalNomal())
    {
        if (true == var_singtel)
        {
            document.getElementById('td7_2').innerHTML = DevInfoDes['s1321a'];
        }
        else if((ProductType == '2') && (curLanguage.toUpperCase() == 'ARABIC'))
{
            document.getElementById('td7_2').innerHTML = DevInfoDes['s1321_xd'];
}
else
{
            document.getElementById('td7_2').innerHTML = DevInfoDes['s1321'];
}
    }
    else
    {
        if (ontPonMode.toUpperCase() == 'GPON')
        {
            if (ontInfo.Status == 'o1' || ontInfo.Status == 'O1')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1322'];
            }
            else if (ontInfo.Status == 'o2' || ontInfo.Status == 'O2')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1323'];
            }
            else if (ontInfo.Status == 'o3' || ontInfo.Status == 'O3')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1324'];
            }
            else if (ontInfo.Status == 'o4' || ontInfo.Status == 'O4')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1325'];
            }
            else if (ontInfo.Status == 'o5' || ontInfo.Status == 'O5')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1326'];
            }
            else if (ontInfo.Status == 'o6' || ontInfo.Status == 'O6')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1327'];
            }
            else if (ontInfo.Status == 'o7' || ontInfo.Status == 'O7')
            {
                document.getElementById('td7_2').innerHTML = htmlencode(ontInfo.Status) + DevInfoDes['s1328'];
            }
        }
        else if (ontPonMode.toUpperCase() == 'EPON')
        {
            if (ontEPONInfo != null)
            {
                if(curLanguage.toUpperCase() == 'CHINESE')
                {
                    if ( "OFFLINE" == ontEPONInfo.Status)
                    {
                        document.getElementById('td7_2').innerHTML = GetLanguageDesc("s020b");
                    }
                    else if("ONLINE" == ontEPONInfo.Status)
                    {
                        document.getElementById('td7_2').innerHTML = GetLanguageDesc("s020c");
                    }
                    else
                    {
                        document.getElementById('td7_2').innerHTML = GetLanguageDesc("s020d");
                    }
                }
                else
                {
                    document.getElementById('td7_2').innerHTML = htmlencode(ontEPONInfo.Status);
                }

            }
            else
            {
                document.getElementById('td7_2').innerHTML = '';
            }
        }
        else
        {
            document.getElementById('td7_2').innerHTML = '';
        }
    }
}

function GetIMEI()
{
    if(CfgMode.toUpperCase()  == 'BYTEL')
    {
        document.getElementById('td17_2Colleft').innerHTML = DevInfoDes['s1613'];
        var strtmp = "00000000000000000000"+ontPonpwd;
        var IMEI = strtmp.substr(strtmp.length -15, strtmp.length -1);
        document.getElementById('td17_2').innerHTML = htmlencode(IMEI);
    }
    else
    {
        document.getElementById('td17_2Row').style.display="none";
    }
}

function GetSnOrMacInfo()
{
    if (ontPonMode.toUpperCase() == 'GPON')
    {
        document.getElementById('td3_2Colleft').innerHTML = DevInfoDes['s1611'];
    }
    else if (ontPonMode.toUpperCase() == 'EPON' || ontPonMode.toUpperCase() == 'GE' || ontPonMode.toUpperCase() == 'WIFI')
    {
        document.getElementById('td3_2Colleft').innerHTML = DevInfoDes['s1612'];
    }
    var  var_deviceMac = "";
    if (ontPonMode.toUpperCase() == 'GPON')
    {
        document.getElementById('td3_2').innerHTML = htmlencode(SN);
    }
    else if (ontPonMode.toUpperCase() == 'EPON' || ontPonMode.toUpperCase() == 'GE' || ontPonMode.toUpperCase() == 'WIFI')
    {
       if (CfgMode.toUpperCase()  == 'BJUNICOM')
       {
            var_deviceMac = deviceInfo.Mac.replace(/\:/g,"-");
            document.getElementById('td3_2').innerHTML = htmlencode(var_deviceMac);
       }
       else
       {
            document.getElementById('td3_2').innerHTML = htmlencode(deviceInfo.Mac);
       }
    }
}
function GetOntId()
{
    if (ontInfo != null)
    {
        document.getElementById('td8_2').innerHTML = htmlencode(ontInfo.ONTID);
    }
    else
    {
        document.getElementById('td8_2').innerHTML = '';
    }
}
function GetCpuUsed()
{
    if (cpuUsed != null)
    {
        document.getElementById('td9_2').innerHTML = htmlencode(cpuUsed);
    }
    else
    {
        document.getElementById('td9_2').innerHTML = '';
    }
}
function GetMemUsed()
{
    if (memUsed != null)
    {
        document.getElementById('td10_2').innerHTML = htmlencode(memUsed);
    }
    else
    {
        document.getElementById('td10_2').innerHTML = '';
    }
}
function GetCustomizeInfo()
{
    if (customizeDes != null)
    {
        document.getElementById('td13_2').innerHTML = htmlencode(customizeDes);
    }
    else
    {
        document.getElementById('td13_2').innerHTML = '';
    }
}
function GoToUserConfig()
{
    window.parent.onMenuChange("userconfig");
}
function OnApply()
{
if (IsPtVdf == 1 || IsPtVdfAP == 1 || IsPtVdfb == 1)
{
return;
}
if (((CfgMode.toUpperCase()=="TELECOM2") || (CfgMode.toUpperCase()=="TELECOM")) && (curUserType != sysUserType))
{
return;
}
    var alias = getValue("DevAlias");
    var Form = new webSubmitForm();
    var RequestFile = "html/ssmp/deviceinfo/deviceinfo.asp";
    Form.addParameter('x.X_HW_DeviceAlias', alias);
    url = 'set.cgi?x=InternetGatewayDevice.DeviceInfo'
        + '&RequestFile=' + RequestFile;
    Form.addParameter('x.X_HW_Token', getValue('onttoken'));
    setDisable('apply',1);
    Form.setAction(url);
    Form.submit();
}

</script>
</head>
<body  class="mainbody" onLoad="LoadFrame();">
<script language="JavaScript" type="text/javascript">
HWCreatePageHeadInfo("deviceinfoasp", GetDescFormArrayById(DevInfoDes, "s0200"), GetDescFormArrayById(DevInfoDes, "s0201"), false);
</script>
<div class="title_spread"></div>
<div BindText="s1619" class="func_title"></div>
<form id="deviceInfoForm" name="deviceInfoForm">
<table id="deviceInfoFormPanel" width="100%" border="0" cellpadding="0" cellspacing="1" class="tabal_noborder_bg">
<script>
    if (ProductType != '2')
    {
        document.write('<li id="td16_2" RealType="HtmlText" DescRef="s0227" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td16_2" InitValue="Empty" />');
    }
</script>
<li id="td1_2" RealType="HtmlText" DescRef="s0202" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td1_2" InitValue="Empty" />
<li id="td2_2" RealType="HtmlText" DescRef="s0203" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td2_2" InitValue="Empty" />
<script>
    if (ProductType == '2')
    {
if ('DZAIN2WIFI' == CfgMode.toUpperCase())
        {
            document.write('<li id="td3_2" RealType="HtmlText" DescRef="s1611_dzain" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td3_2" InitValue="Empty" />');
        }
        else
        {
document.write('<li id="td3_2" RealType="HtmlText" DescRef="s1611" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td3_2" InitValue="Empty" />');
}
    }
    else
    {
        document.write('<li id="td3_2" RealType="HtmlText" DescRef="Empty" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td3_2" InitValue="Empty" />');
    }
    if (ProductType != '2')
    {
        document.write('<li id="td17_2" RealType="HtmlText" DescRef="Empty" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td17_2" InitValue="Empty" />');
    }
</script>
<li id="td4_2" RealType="HtmlText" DescRef="s0204" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td4_2" InitValue="Empty" />
<li id="td5_2" RealType="HtmlText" DescRef="s0205" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td5_2" InitValue="Empty" />
<script>
if (CfgMode.toUpperCase() == 'ROSUNION')
    {
        document.write('<li id="td6_2" RealType="HtmlText" DescRef="s0217r" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td6_2" InitValue="Empty" />');
    }
    else
    {
        document.write('<li id="td6_2" RealType="HtmlText" DescRef="s0217" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td6_2" InitValue="Empty" />');    
    }
    if (ProductType == '2')
    {
        document.write('<li id="td7_2" RealType="HtmlText" DescRef="s1612" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td7_2" InitValue="Empty" />');
    }
    else
    {
        document.write('<li id="td7_2" RealType="HtmlText" DescRef="s0206" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td7_2" InitValue="Empty" />');    
    }

if((ProductType == '2') && (curLanguage.toUpperCase() == 'ARABIC'))
{
document.write('<li id="td8_2" RealType="HtmlText" DescRef="s0207_xd" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td8_2" InitValue="Empty" />');
}
else
{
document.write('<li id="td8_2" RealType="HtmlText" DescRef="s0207" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td8_2" InitValue="Empty" />'); 
}
</script>
<li id="td9_2" RealType="HtmlText" DescRef="s0208" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td9_2" InitValue="Empty" />
<li id="td10_2" RealType="HtmlText" DescRef="s0209" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td10_2" InitValue="Empty" />
<li id="td11_2" RealType="HtmlText" DescRef="s020a" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td11_2" InitValue="Empty" />
<script language="JavaScript" type="text/javascript">
    if (CfgMode.toUpperCase() == 'TELECENTRO')
    {
        document.write('<li id="ShowTime" RealType="HtmlText" DescRef="s021a" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="ShowTime" InitValue="Empty" />');
    }
    else
    {
        document.write('<li id="ShowTime" RealType="HtmlText" DescRef="s020e" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="ShowTime" InitValue="Empty" />');
    }
</script>
<li id="td13_2" RealType="HtmlText" DescRef="s0225" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td13_2" InitValue="Empty" />
<li id="td14_2" RealType="HtmlText" DescRef="s0226" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td14_2" InitValue="Empty" />
<script>
    if (ProductType != '2')
    {
        document.write('<li id="td15_2" RealType="HtmlText" DescRef="s1615" RemarkRef="Empty" ErrorMsgRef="Empty" Require="FALSE" BindField="td15_2" InitValue="Empty" />');
    }
</script>
</table>
<script>
var TableClass = new stTableClass("width_per25", "table_right align_left","ltr");
var deviceInfoFormList = new Array();
deviceInfoFormList = HWGetLiIdListByForm("deviceInfoForm",null);
if(typeof(DeviceinfoReload) == "undefined")
{
    DeviceinfoReload = null;
}
HWParsePageControlByID("deviceInfoForm",TableClass,DevInfoDes,DeviceinfoReload);
document.getElementById('td1_2').innerHTML = htmlencode(deviceInfo.ModelName);
document.getElementById('td2_2').innerHTML = htmlencode(deviceInfo.Description);
if (ProductType == '2')
{
    document.getElementById('td3_2').innerHTML = htmlencode(SN);
}
if (ProductType != '2')
{
    GetSnOrMacInfo();
    GetIMEI();
}
document.getElementById('td4_2').innerHTML = htmlencode(deviceInfo.HardwareVersion);
document.getElementById('td5_2').innerHTML = htmlencode(deviceInfo.SoftwareVersion);
if (CfgMode.toUpperCase() == 'ROSUNION')
{
document.getElementById('td6_2').innerHTML = htmlencode("Huawei Technologies Co., Ltd");
}
else
{
document.getElementById('td6_2').innerHTML = htmlencode(deviceInfo.ManufactureInfo);
}
if (ProductType == '2')
{
    document.getElementById('td7_2').innerHTML = htmlencode(deviceInfo.Mac.toUpperCase());
}
else
{
    GetONTRegisterStatus();
    GetOntId();
}
GetCpuUsed();
GetMemUsed();

if(CfgMode.toUpperCase() != 'SINGTEL' && CfgMode.toUpperCase() != 'SINGTEL2')
{
    GetCustomizeInfo();
}

if (ProductType != '2')
{
    document.getElementById('td11_2').innerHTML = htmlencode(ONTUserServices);
    document.getElementById('td15_2').innerHTML = htmlencode(deviceTag);
}
</script>
</form>
<div class="func_spread"></div>
<div id=devicealias>
<div BindText="s1616" class="func_title"></div>
<div>
    <table width="100%" border="0" cellpadding="0" cellspacing="1" class="tabal_noborder_bg">
        <tr>
            <td BindText="s1617" class="table_title width_per25"></td>
            <td class="table_right width_per75">
                <input class="width_per60" type="text" id="DevAlias" value = "">
            </td>            
        </tr>        
    </table>
    <table width="100%" height="30"> 
        <tr>
            <td class='title_bright1'>
                <button id="apply" BindText="s1618" class="ApplyButtoncss" type="button" onClick="OnApply();" enable=true  ></button>
            </td>
        </tr>
        <input type="hidden" name="onttoken" id="hwonttoken" value="9f440898ce496ffd2c42b254765dfca2">
    </table> 
</div>
</div>
<script>
        ParseBindTextByTagName(DevInfoDes, "div", 1);
        ParseBindTextByTagName(DevInfoDes, "button", 1);
        ParseBindTextByTagName(DevInfoDes, "input", 2);
</script>
<div class="func_spread"></div>
<table width="100%" border="0" cellpadding="0" cellspacing="0" class="tabal_bg">
<tr id="DefaultNotice" style="display:none">
<script language="JavaScript" type="text/javascript">
if ( 'ZAIN' == CfgMode.toUpperCase())
{
    document.write('<td class="table_title" id="td13_1" BindText="s2016" style="color: #e0218a; background-color: #ffffff;"></td>');
}
else if ("COMMONEBG2WIFI" == CfgMode.toUpperCase() || deviceInfo.ModelName.substr(0,2) == "EG" || ("DBAHNHOF2WIFI" == CfgMode.toUpperCase()))
{
document.write('<td class="table_title" id="td13_1" BindText="s2016_ebg" style="color:#FF0000"></td>');
}
else
{
    document.write('<td class="table_title" id="td13_1" BindText="s2016" style="color:#FF0000"></td>');
}
</script>
</tr>
</table>
<div style="height:20px"></div>
</body>
</html>
