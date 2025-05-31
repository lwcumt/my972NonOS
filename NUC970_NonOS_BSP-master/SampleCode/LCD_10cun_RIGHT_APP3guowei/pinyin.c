#include"pinyin.h"


//"Æ´ÒôÊäÈë·¨ºº×ÖÅÅÁĞ±í"
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"°¡°¢ß¹àÄëçï¹"};
const unsigned char PY_mb_ai    []={"°£°¤°¥°¦°§°¨°©°ª°«°¬°­°®°¯ŞßàÈàÉæÈè¨êÓíÁïÍö°"};
const unsigned char PY_mb_an    []={"°°°±°²°³°´°µ°¶°·°¸ÚÏÛûŞîáíâÖèñï§ğÆ÷ö"};
const unsigned char PY_mb_ang   []={"°º°»°¹"};
const unsigned char PY_mb_ao    []={"°¼°½°¾°¿°À°Á°Â°Ã°ÄÛêŞÖà»á®âÚåÛæÁæñéáñúòüöË÷¡÷é"};
const unsigned char PY_mb_ba    []={"°Å°Æ°Ç°È°É°Ê°Ë°Ì°Í°Î°Ï°Ğ°Ñ°Ò°Ó°Ô°Õ°ÖÜØİÃá±å±îÙôÎöÑ÷É"};
const unsigned char PY_mb_bai   []={"°×°Ø°Ù°Ú°Û°Ü°İ°Ş²®Şãêş"};
const unsigned char PY_mb_ban   []={"°ß°à°á°â°ã°ä°å°æ°ç°è°é°ê°ë°ì°íÚæÛàêÚîÓñ£ñ­ô²"};
const unsigned char PY_mb_bang  []={"°î°ï°ğ°ñ°ò°ó°ô°õ°ö°÷°ø°ùİòäº"};
const unsigned char PY_mb_bao   []={"°ú°û°ü°ı°ş±¡±¢±£±¤±¥±¦±§±¨±©±ª±«±¬ÅÙÅÚÙèİáæßìÒğ±ñÙõÀöµ"};
const unsigned char PY_mb_bei   []={"±­±®±¯±°±±±²±³±´±µ±¶±·±¸±¹±º±»±ÛØÃÚéÚıÛıİÉİíßÂã£íÕğÇñØöÍ÷¹"};
const unsigned char PY_mb_ben   []={"±¼±½±¾±¿ÛÎÛĞêÚï¼"};
const unsigned char PY_mb_beng  []={"°ö±À±Á±Â±Ã±Ä±ÅÜ¡àÔê´"};
const unsigned char PY_mb_bi    []={"±Æ±Ç±È±É±Ê±Ë±Ì±Í±Î±Ï±Ğ±Ñ±Ò±Ó±Ô±Õ±Ö±×±Ø±Ù±Ú±Û±Ü±İÃØÃÚØ°ÙÂÛıÜÅÜêİ©İÉŞµßÁßÙáùâØã¹ääå¨åöåşæ¾æÔèµêÚî¯îéïõñÔóÙóëó÷ô°ôÅõÏ÷Â"};
const unsigned char PY_mb_bian  []={"±Ş±ß±à±á±â±ã±ä±å±æ±ç±è±éØÒÛÍÜĞâíãêçÂìÔí¾íÜñ¹ñÛòùóÖöı"};
const unsigned char PY_mb_biao  []={"±ê±ë±ì±íæ»æôè¼ì©ì­ì®ìáïÚïğñ¦ñÑ÷§÷Ô"};
const unsigned char PY_mb_bie   []={"±î±ï±ğ±ñõ¿"};
const unsigned char PY_mb_bin   []={"±ò±ó±ô±õ±ö±÷ÙÏáÙçÍçãéÄéëë÷ïÙ÷Æ÷Ş"};
const unsigned char PY_mb_bing  []={"±ø±ù±ú±û±ü±ı±ş²¡²¢ÆÁÙ÷ÙûÚûŞğéÄ"};
const unsigned char PY_mb_bo    []={"°Ø°Ù°ş±¡²£²¤²¥²¦²§²¨²©²ª²«²¬²­²®²¯²°²±²²²³²´²µ²·ØÃÙñŞ¬à£âÄéŞë¢íçîàğ¾ô¤õÀõËõÛ"};
const unsigned char PY_mb_bu    []={"²½²¼±¤²¶²·²¸²¹²º²»²¾²¿²ÀÆÒß²åÍê³êÎîĞîßõ³"};
const unsigned char PY_mb_ca    []={"²Áàêíå"};
const unsigned char PY_mb_cai   []={"²Â²Ã²Ä²Å²Æ²Ç²È²É²Ê²Ë²Ì"};
const unsigned char PY_mb_can   []={"²Í²Î²Ï²Ğ²Ñ²Ò²Óåîæîè²ôÓ÷õ"};
const unsigned char PY_mb_cang  []={"²Ô²Õ²Ö²×²ØØ÷"};
const unsigned char PY_mb_cao   []={"²Ù²Ú²Û²Ü²İÜ³àĞäîó©ô½"};
const unsigned char PY_mb_ce    []={"²Ş²ß²à²á²ââü"};
const unsigned char PY_mb_cen   []={"²Îá¯ä¹"}; 
const unsigned char PY_mb_ceng  []={"²ã²äÔøàá"};
const unsigned char PY_mb_cha   []={"²å²æ²ç²è²é²ê²ë²ì²í²î²ïÉ²ÔûàêâªâÇãâæ±è¾é«é¶éßïÊïïñÃ"};
const unsigned char PY_mb_chai  []={"²î²ğ²ñ²òÙ­îÎğûò²ö·"};
const unsigned char PY_mb_chan  []={"²ó²ô²õ²ö²÷²ø²ù²ú²û²üµ¥ÙæÚÆİÛâÜâãäıå¤åîåñæ¿êèìøïâó¸õğ"};
const unsigned char PY_mb_chang []={"²ı²ş³¡³¢³£³¤³¥³¦³§³¨³©³ª³«ØöÛËÜÉİÅáäâêã®ãÑæ½æÏêÆë©öğ"};
const unsigned char PY_mb_chao  []={"³¬³­³®³¯³°³±³²³³³´´Â½Ëâ÷êËñé"};
const unsigned char PY_mb_che   []={"³µ³¶³·³¸³¹³ºÛååøíº"};
const unsigned char PY_mb_chen  []={"³»³¼³½³¾³¿³À³Á³Â³Ã³Ä³ÆÚÈÚßŞÓàÁå·è¡é´í×ö³"};
const unsigned char PY_mb_cheng []={"³Å³Æ³Ç³È³É³Ê³Ë³Ì³Í³Î³Ï³Ğ³Ñ³Ò³ÓÊ¢Ø©ÛôàááçèÇèßëóîªîñîõñÎòÉõ¨"};
const unsigned char PY_mb_chi   []={"³Ô³Õ³Ö³×³Ø³Ù³Ú³Û³Ü³İ³Ş³ß³à³á³â³ãÙÑÛæÜ¯Üİß³ßêà´àÍáÜâÁæÊë·í÷ğ·ñ¡ñİò¿ó¤ó×óøôùõØ÷Î"};
const unsigned char PY_mb_chong []={"³ä³å³æ³ç³èÖÖÖØÜûâçã¿ï¥ô©ô¾"};
const unsigned char PY_mb_chou  []={"³é³ê³ë³ì³í³î³ï³ğ³ñ³ò³ó³ôÙ±àüã°ñ¬öÅ"};
const unsigned char PY_mb_chu   []={"³õ³ö³÷³ø³ù³ú³û³ü³ı³ş´¡´¢´£´¤´¥´¦ĞóØ¡Û»âğãÀç©èÆèúéËñÒòÜõé÷í"};
const unsigned char PY_mb_chuai []={"´§ŞõàÜëúõß"};
const unsigned char PY_mb_chuan []={"´¨´©´ª´«´¬´­´®â¶å×çİë°îËô­"};
const unsigned char PY_mb_chuang[]={"´¯´°´±´²´³´´âëğÚ"};
const unsigned char PY_mb_chui  []={"´µ´¶´·´¸´¹Úïé¢é³"};
const unsigned char PY_mb_chun  []={"´º´»´¼´½´¾´¿´Àİ»ğÈòí"};
const unsigned char PY_mb_chuo  []={"´Á´Âà¨åÁê¡õÖöº"};
const unsigned char PY_mb_ci    []={"²î´Ã´Ä´Å´Æ´Ç´È´É´Ê´Ë´Ì´Í´ÎËÅ×ÈÜëßÚìôğËôÒôÙ"};
const unsigned char PY_mb_cong  []={"´Ï´Ğ´Ñ´Ò´Ó´ÔÜÊäÈæõçıè®èÈ"};
const unsigned char PY_mb_cou   []={"´Õé¨ê£ëí"};
const unsigned char PY_mb_cu    []={"´Ö´×´Ø´ÙİıáŞâ§éãõ¡õ¾õí"};
const unsigned char PY_mb_cuan  []={"´Ú´Û´ÜÔÜÙàß¥ìàïé"};
const unsigned char PY_mb_cui   []={"´İ´Ş´ß´à´á´â´ã´äİÍßıã²è­éÁë¥ö¿"};
const unsigned char PY_mb_cun   []={"´å´æ´çââñå"};
const unsigned char PY_mb_cuo   []={"´è´é´ê´ë´ì´íØÈáÏëâï±ïóğîğûõºõãõò"};
const unsigned char PY_mb_da    []={"´î´ï´ğ´ñ´ò´óŞÇßÕàªâòæ§í³ğãñ×óÎ÷°÷²"};
const unsigned char PY_mb_dai   []={"´ó´ô´õ´ö´÷´ø´ù´ú´û´ü´ı´şµ¡Ü¤ß°ß¾á·åÊææçªçé÷ì"};
const unsigned char PY_mb_dan   []={"µ¢µ£µ¤µ¥µ¦µ§µ¨µ©µªµ«µ¬µ­µ®µ¯µ°ÉÄÊ¯ÙÙİÌà¢å£ééêæíñğãğ÷ñõóì"};
const unsigned char PY_mb_dang  []={"µ±µ²µ³µ´µµÚÔÛÊİĞå´í¸îõñÉ"};
const unsigned char PY_mb_dao   []={"µ¶µ·µ¸µ¹µºµ»µ¼µ½µ¾µ¿µÀµÁØÖß¶àüâáë®ìâôî"};
const unsigned char PY_mb_de    []={"µÂµÃµÄµØï½"};
const unsigned char PY_mb_dei   []={"µÃ"};
const unsigned char PY_mb_deng  []={"³ÎµÅµÆµÇµÈµÉµÊµËàâáØê­íãïëô£"};
const unsigned char PY_mb_di    []={"µÄµÌµÍµÎµÏµĞµÑµÒµÓµÔµÕµÖµ×µØµÙµÚµÛµÜµİµŞÌáØµÙáÚ®ÚĞÛ¡Ûæİ¶àÖæ·èÜé¦êëíÆíÚíûïáôÆ÷¾"};
const unsigned char PY_mb_dia   []={"àÇ"};
const unsigned char PY_mb_dian  []={"µßµàµáµâµãµäµåµæµçµèµéµêµëµìµíµîÚçÛãáÛçèîäñ°ñ²ô¡õÚ"};
const unsigned char PY_mb_diao  []={"µïµğµñµòµóµôµõµöµ÷îöï¢õõöô"};
const unsigned char PY_mb_die   []={"µøµùµúµûµüµıµşÛìÜ¦Şéà©ëºğ¬ñóõŞöø"};
const unsigned char PY_mb_ding  []={"¶¡¶¢¶£¶¤¶¥¶¦¶§¶¨¶©Øêà¤çàëëíÖî®îúğÛñôôú"};
const unsigned char PY_mb_diu   []={"¶ªîû"};
const unsigned char PY_mb_dong  []={"¶«¶¬¶­¶®¶¯¶°¶±¶²¶³¶´ßËá´á¼ë±ëËëØíÏğ´"};
const unsigned char PY_mb_dou   []={"¶µ¶¶¶·¶¸¶¹¶º¶»¶¼İúñ¼ò½óû"};
const unsigned char PY_mb_du    []={"¶¼¶½¶¾¶¿¶À¶Á¶Â¶Ã¶Ä¶Å¶Æ¶Ç¶È¶É¶ÊÜ¶à½äÂèüë¹ó¼óÆ÷Ç÷ò"};
const unsigned char PY_mb_duan  []={"¶Ë¶Ì¶Í¶Î¶Ï¶Ğé²ìÑóı"};
const unsigned char PY_mb_dui   []={"¶Ñ¶Ò¶Ó¶Ôí¡í­íÔ"};
const unsigned char PY_mb_dun   []={"¶Õ¶Ö¶×¶Ø¶Ù¶Ú¶Û¶Ü¶İãçìÀí»íâíïïæõ»"};
const unsigned char PY_mb_duo   []={"¶È¶Ş¶ß¶à¶á¶â¶ã¶ä¶å¶æ¶ç¶è¶éÍÔßÍßáãõç¶îìñÖõâ"};
const unsigned char PY_mb_e     []={"°¢¶ê¶ë¶ì¶í¶î¶ï¶ğ¶ñ¶ò¶ó¶ô¶õ¶öÅ¶Ø¬ÚÌÛÑÜÃİ­İàßÀãµåíæ¹éîëñï°ïÉğÊò¦öù"};
const unsigned char PY_mb_ei    []={"ÚÀ"};
const unsigned char PY_mb_en    []={"¶÷àÅİìŞô"};
const unsigned char PY_mb_er    []={"¶ø¶ù¶ú¶û¶ü¶ı¶ş·¡åÇçíîïğ¹öÜ"};
const unsigned char PY_mb_fa    []={"·¢·£·¤·¥·¦·§·¨·©ÛÒíÀ"};
const unsigned char PY_mb_fan   []={"·ª·«·¬·­·®·¯·°·±·²·³·´·µ·¶···¸·¹·ºŞ¬ŞÀá¦èóìÜî²õì"};
const unsigned char PY_mb_fang  []={"·»·¼·½·¾·¿·À·Á·Â·Ã·Ä·ÅØÎÚúèÊîÕô³öĞ"};
const unsigned char PY_mb_fei   []={"·Æ·Ç·È·É·Ê·Ë·Ì·Í·Î·Ï·Ğ·ÑÜÀáôã­äÇåúç³é¼êÚëèì³ìéíÉïĞğòòãóõôäö­öî"};
const unsigned char PY_mb_fen   []={"·Ò·Ó·Ô·Õ·Ö·×·Ø·Ù·Ú·Û·Ü·İ·Ş·ß·àÙÇå¯çãèûêÚö÷÷÷"};
const unsigned char PY_mb_feng  []={"·á·â·ã·ä·å·æ·ç·è·é·ê·ë·ì·í·î·ïÙºÛºİ×ßôããí¿"};
const unsigned char PY_mb_fo    []={"·ğ"};
const unsigned char PY_mb_fou   []={"·ñó¾"};
const unsigned char PY_mb_fu    []={"·ğ·ò·ó·ô·õ·ö·÷·ø·ù·ú·û·ü·ı·ş¸¡¸¢¸£¸¤¸¥¸¦¸§¸¨¸©¸ª¸«¸¬¸­¸®¸¯¸°¸±¸²¸³¸´¸µ¸¶¸·¸¸¸¹¸º¸»¸¼¸½¸¾¸¿¸ÀÙëÙìÚâÛ®Ü½ÜÀÜŞÜòİ³İÊŞÔß»á¥âöäæåõæÚæâç¦ç¨èõêçìğíÉíêíëî·ïûğ¥ò¶òİòğòóôïõÃõÆöÖöû"};
const unsigned char PY_mb_ga    []={"¸Á¸Â¼Ğ¿§Ù¤ŞÎæØæÙê¸îÅ"};
const unsigned char PY_mb_gai   []={"¸Ã¸Ä¸Å¸Æ¸Ç¸È½æØ¤ÚëÛòê®êàëÜ"};
const unsigned char PY_mb_gan   []={"¸É¸Ê¸Ë¸Ì¸Í¸Î¸Ï¸Ğ¸Ñ¸Ò¸ÓÛáÜÕŞÏß¦ãïäÆä÷ç¤éÏêºí·ğáôû"};
const unsigned char PY_mb_gang  []={"¸Ô¸Õ¸Ö¸×¸Ø¸Ù¸Ú¸Û¸Ü¿¸í°î¸óà"};
const unsigned char PY_mb_gao   []={"¸İ¸Ş¸ß¸à¸á¸â¸ã¸ä¸å¸æØºÚ¾Û¬Ş»çÉéÀéÂê½ï¯"};
const unsigned char PY_mb_ge    []={"¸Ç¸ç¸è¸é¸ê¸ë¸ì¸í¸î¸ï¸ğ¸ñ¸ò¸ó¸ô¸õ¸ö¸÷ºÏ¿©ØªØîÛÁÛÙÜªàÃæüë¡ëõîşïÓñËò´ô´÷À"};
const unsigned char PY_mb_gei   []={"¸ø"};
const unsigned char PY_mb_gen   []={"¸ù¸úØ¨İ¢ßçôŞ"};
const unsigned char PY_mb_geng  []={"¸û¸ü¸ı¸ş¹¡¹¢¹£¾±ßìâÙç®öá"};
const unsigned char PY_mb_gong  []={"¹¤¹¥¹¦¹§¹¨¹©¹ª¹«¹¬¹­¹®¹¯¹°¹±¹²ŞÃçîëÅò¼ö¡"};
const unsigned char PY_mb_gou   []={"¹³¹´¹µ¹¶¹·¹¸¹¹¹º¹»ØşÚ¸á¸åÜæÅçÃèÛêíì°óÑóô÷¸"};
const unsigned char PY_mb_gu    []={"¹¼¹½¹¾¹¿¹À¹Á¹Â¹Ã¹Ä¹Å¹Æ¹Ç¹È¹É¹Ê¹Ë¹Ì¹Í¼ÖØÅÚ¬İÔáÄãéèôéïêôêöëûì±î­î¹îÜïÀğ³ğÀğóòÁôşõıöñ÷½"};
const unsigned char PY_mb_gua   []={"¹Î¹Ï¹Ğ¹Ñ¹Ò¹ÓØÔÚ´ßÉèéëÒğ»"};
const unsigned char PY_mb_guai  []={"¹Ô¹Õ¹ÖŞâ"};
const unsigned char PY_mb_guan  []={"¹×¹Ø¹Ù¹Ú¹Û¹Ü¹İ¹Ş¹ß¹à¹áÂÚÙÄİ¸ŞèäÊîÂğÙ÷¤"};
const unsigned char PY_mb_guang []={"¹â¹ã¹äßÛáîèæë×"};
const unsigned char PY_mb_gui   []={"¹å¹æ¹ç¹è¹é¹ê¹ë¹ì¹í¹î¹ï¹ğ¹ñ¹ò¹ó¹ôÈ²ØĞØÛâÑå³æ£èíêÁêĞğ§óşöÙ÷¬"};
const unsigned char PY_mb_gun   []={"¹õ¹ö¹÷ÙòçµíŞöç"};
const unsigned char PY_mb_guo   []={"¹ø¹ù¹ú¹û¹ü¹ıÎĞÙåÛöŞâßÃàşáÆâ£é¤ë½ï¾ñøòäòå"};
const unsigned char PY_mb_ha    []={"¸ò¹şîş"};
const unsigned char PY_mb_hai   []={"º¡º¢º£º¤º¥º¦º§»¹¿ÈàËëÜõ°"};
const unsigned char PY_mb_han   []={"º¨º©ºªº«º¬º­º®º¯º°º±º²º³º´ºµº¶º·º¸º¹ººÚõİÕŞşå«êÏìÊñüò¥òÀ÷ı"};
const unsigned char PY_mb_hang  []={"º»º¼º½¿ÔÏïĞĞãìç¬ñş"};
const unsigned char PY_mb_hao   []={"¸äº¾º¿ºÀºÁºÂºÃºÄºÅºÆºÑİïŞ¶àÆàãå©å°ê»ğ©ò«òº"};
const unsigned char PY_mb_he    []={"ºÇºÈºÉºÊºËºÌºÍºÎºÏºĞºÑºÒºÓºÔºÕºÖº×ºØÏÅÚ­ÛÀÛÖàÀãØæüêÂîÁò¢òÂôç"};
const unsigned char PY_mb_hei   []={"ºÙºÚ"};
const unsigned char PY_mb_hen   []={"ºÛºÜºİºŞ"};
const unsigned char PY_mb_heng  []={"ºßºàºáºâºãŞ¿çñèì"};
const unsigned char PY_mb_hong  []={"ºäºåºæºçºèºéºêºëºìÙäÙêÚ§İ¦Ş®Ş°ãÈãü"};
const unsigned char PY_mb_hou   []={"ºíºîºïºğºñºòºóÜ©ááåËğúóóô×ö×÷¿"};
const unsigned char PY_mb_hu    []={"ºËºôºõºöº÷ºøºùºúºûºüºıºş»¡»¢»£»¤»¥»¦»§Ùüßüàñá²â©âïã±ä°äïçúéÎéõì²ìÃìÎìæìèìïğ­ğÀğÉğ×ò®óËõ­õú÷½"};
const unsigned char PY_mb_hua   []={"»¨»©»ª»«»¬»­»®»¯»°æèèëí¹îü"};
const unsigned char PY_mb_huai  []={"»±»²»³»´»µõ×"};
const unsigned char PY_mb_huan  []={"»¶»·»¸»¹»º»»»¼»½»¾»¿»À»Á»Â»ÃÛ¨Û¼ÛùİÈß§à÷âµä¡ä½äñå¾åÕçÙïÌöé÷ß"};
const unsigned char PY_mb_huang []={"»Ä»Å»Æ»Ç»È»É»Ê»Ë»Ì»Í»Î»Ï»Ğ»ÑÚòáåäÒäêåØè«ëÁñ¥ó¨óòöü"};
const unsigned char PY_mb_hui   []={"»Ò»Ó»Ô»Õ»Ö»×»Ø»Ù»Ú»Û»Ü»İ»Ş»ß»à»á»â»ã»ä»å»æÀ£Ú¶ÜîÜöŞ¥ßÔßÜà¹ãÄä§ä«åççÀèíêÍí£ò³ó³÷â"};
const unsigned char PY_mb_hun   []={"»ç»è»é»ê»ë»ìÚ»âÆãÔäãçõ"};
const unsigned char PY_mb_huo   []={"ºÍ»í»î»ï»ğ»ñ»ò»ó»ô»õ»öØåŞ½ß«àëâ·îØïÁïìñëó¶"};
const unsigned char PY_mb_ji    []={"¸ø»÷»ø»ù»ú»û»ü»ı»ş¼¡¼¢¼£¼¤¼¥¼¦¼§¼¨¼©¼ª¼«¼¬¼­¼®¼¯¼°¼±¼²¼³¼´¼µ¼¶¼·¼¸¼¹¼º¼»¼¼¼½¼¾¼¿¼À¼Á¼Â¼Ã¼Ä¼Å¼Æ¼Ç¼È¼É¼Ê¼Ë¼Ì¼Í½åÆæÏµØ¢Ø½ØÀØŞÙ¥ÙÊÛÔÜ¸ÜÁÜùİ½İğŞªŞáß´ßÒßâßóá§áÕä©åæåìæ÷çÜçáé®éêêªê«êåêéê÷ì´í¶î¿ïúğ¢ñ¤ò±óÅóÇôßõÒõÕö«öİöê÷Ù÷ä"};
const unsigned char PY_mb_jia   []={"¼Î¼Ï¼Ğ¼Ñ¼Ò¼Ó¼Ô¼Õ¼Ö¼×¼Ø¼Ù¼Ú¼Û¼Ü¼İ¼ŞÇÑØÅÙ¤Û£İçáµä¤åÈçìê©ëÎí¢îòîşïØğèğıñÊòÌóÕôÂõÊ"};
const unsigned char PY_mb_jian  []={"¼ß¼à¼á¼â¼ã¼ä¼å¼æ¼ç¼è¼é¼ê¼ë¼ì¼í¼î¼ï¼ğ¼ñ¼ò¼ó¼ô¼õ¼ö¼÷¼ø¼ù¼ú¼û¼ü¼ı¼ş½¡½¢½£½¤½¥½¦½§½¨ÙÔÚÉÚÙÚÚİÑİóŞöàîäÕå¿åÀçÌèÅé¥ê§ê¯êğêùë¦ëìíúïµğÏñĞóÈôåõÂõİöä÷µ"};
const unsigned char PY_mb_jiang []={"ºç½©½ª½«½¬½­½®½¯½°½±½²½³½´½µÇ¿Üüä®ç­çÖêñíäñğôİôø"};
const unsigned char PY_mb_jiao  []={"½¶½·½¸½¹½º½»½¼½½½¾½¿½À½Á½Â½Ã½Ä½Å½Æ½Ç½È½É½Ê½Ë½Ì½Í½Î½Ï½Ğ½Ñ¾õĞ£Ù®ÙÕÜ´ÜúŞØàİá½áèæ¯ë¸ğ¨ğÔòÔõ´õÓöŞ"};
const unsigned char PY_mb_jie   []={"½Ò½Ó½Ô½Õ½Ö½×½Ø½Ù½Ú½Û½Ü½İ½Ş½ß½à½á½â½ã½ä½å½æ½ç½è½é½ê½ë½ìÙÊÚ¦ÚµÚàŞ×à®àµæ¼æİèîíÙïÇğÜò¡ò»ôÉöÚ÷º"};
const unsigned char PY_mb_jin   []={"½í½î½ï½ğ½ñ½ò½ó½ô½õ½ö½÷½ø½ù½ú½û½ü½ı½ş¾¡¾¢Úáİ£İÀàäâËâÛæ¡çÆèªéÈêáêîîÄñÆñæ"};
const unsigned char PY_mb_jing  []={"¾¢¾£¾¤¾¥¾¦¾§¾¨¾©¾ª¾«¾¬¾­¾®¾¯¾°¾±¾²¾³¾´¾µ¾¶¾·¾¸¾¹¾º¾»ØÙÙÓÚåÚêİ¼â°ã½ãşåÉåòæºëÂëÖëæìºö¦"};
const unsigned char PY_mb_jiong []={"¾¼¾½ØçåÄìç"};
const unsigned char PY_mb_jiu   []={"¾¾¾¿¾À¾Á¾Â¾Ã¾Ä¾Å¾Æ¾Ç¾È¾É¾Ê¾Ë¾Ì¾Í¾ÎÙÖà±ãÎèÑèêğ¯ğÕôñ÷İ"};
const unsigned char PY_mb_ju    []={"³µ¹ñ¾Ï¾Ğ¾Ñ¾Ò¾Ó¾Ô¾Õ¾Ö¾×¾Ø¾Ù¾Ú¾Û¾Ü¾İ¾Ş¾ß¾à¾á¾â¾ã¾ä¾å¾æ¾çÙÆÚªÜÄÜÚÜìŞäåáåğè¢èÛé§é°é·éÙêøì«îÒï¸ñÀñÕôòõ¶õáö´öÂöÄ÷¶"};
const unsigned char PY_mb_juan  []={"¾è¾é¾ê¾ë¾ì¾í¾îÈ¦Û²áúä¸èğîÃïÃïÔöÁ"};
const unsigned char PY_mb_jue   []={"½À½Å½Ç¾ï¾ğ¾ñ¾ò¾ó¾ô¾õ¾ö¾÷¾øØÊØãÚÜÛÇÜ¥Ş§àÙáÈâ±æŞçåèöéÓìßïãõêõû"};
const unsigned char PY_mb_jun   []={"¹ê¾ù¾ú¾û¾ü¾ı¾ş¿¡¿¢¿£¿¤¿¥ŞÜñäóŞ÷å"};
const unsigned char PY_mb_ka    []={"¿¦¿§¿¨¿©ØûßÇëÌ"};
const unsigned char PY_mb_kai   []={"¿ª¿«¿¬¿­¿®ØÜÛîİÜâéâıîøï´ïÇ"};
const unsigned char PY_mb_kan   []={"¼÷¿¯¿°¿±¿²¿³¿´Ù©ÛÉİ¨ãÛê¬íèî«"};
const unsigned char PY_mb_kang  []={"¿µ¿¶¿·¿¸¿¹¿º¿»ØøãÊîÖ"};
const unsigned char PY_mb_kao   []={"¿¼¿½¿¾¿¿åêèàêûîí"};
const unsigned char PY_mb_ke    []={"ºÇ¿À¿Á¿Â¿Ã¿Ä¿Å¿Æ¿Ç¿È¿É¿Ê¿Ë¿Ì¿Í¿Îà¾á³ã¡äÛæìç¼çæéğë´î§îİîşï¾ïığâñ½ò¤òÂòò÷Á"};
const unsigned char PY_mb_ken   []={"¿Ï¿Ğ¿Ñ¿ÒñÌ"};
const unsigned char PY_mb_keng  []={"¿Ó¿ÔëÖîïï¬"};
const unsigned char PY_mb_kong  []={"¿Õ¿Ö¿×¿ØÙÅáÇóí"};
const unsigned char PY_mb_kou   []={"¿Ù¿Ú¿Û¿ÜÜÒŞ¢ßµíîóØ"};
const unsigned char PY_mb_ku    []={"¿İ¿Ş¿ß¿à¿á¿â¿ãØÚÜ¥à·ç«÷¼"};
const unsigned char PY_mb_kua   []={"¿ä¿å¿æ¿ç¿èÙ¨ï¾"};
const unsigned char PY_mb_kuai  []={"»á¿é¿ê¿ë¿ìØáÛ¦ßàáöëÚ"};
const unsigned char PY_mb_kuan  []={"¿í¿î÷Å"};
const unsigned char PY_mb_kuang []={"¿ï¿ğ¿ñ¿ò¿ó¿ô¿õ¿öÚ²Ú¿Ú÷ÛÛŞÅßÑæşêÜ"};
const unsigned char PY_mb_kui   []={"¿÷¿ø¿ù¿ú¿û¿ü¿ı¿şÀ¡À¢À£Ø¸ØÑÙçÚóİŞŞñà­à°ã¦ã´åÓêÒî¥ñùòñóñõÍ"};
const unsigned char PY_mb_kun   []={"À¤À¥À¦À§ã§ãÍçûï¿õ«öï÷Õ"};
const unsigned char PY_mb_kuo   []={"À¨À©ÀªÀ«òÒ"};
const unsigned char PY_mb_la    []={"À¬À­À®À¯À°À±À²ÂäØİååê¹íÇğø"};
const unsigned char PY_mb_lai   []={"À³À´ÀµáÁáâäµäşêãíùïªñ®ô¥"};
const unsigned char PY_mb_lan   []={"À¶À·À¸À¹ÀºÀ»À¼À½À¾À¿ÀÀÀÁÀÂÀÃÀÄá°äíé­ìµî½ïçñÜ"};
const unsigned char PY_mb_lang  []={"ÀÅÀÆÀÇÀÈÀÉÀÊÀËİ¹İõà¥ãÏï¶ïüòë"};
const unsigned char PY_mb_lao   []={"ÀÌÀÍÀÎÀÏÀĞÀÑÀÒÀÓÀÔÂäÂçßëáÀèáîîï©ğìñìõ²"};
const unsigned char PY_mb_le    []={"ÀÕÀÖÁËØìß·ãî÷¦"};
const unsigned char PY_mb_lei   []={"ÀÕÀ×ÀØÀÙÀÚÀÛÀÜÀİÀŞÀßÀàÀáÙúÚ³àÏæĞçĞéÛñçõª"};
const unsigned char PY_mb_leng  []={"ÀâÀãÀäÜ¨ã¶"};
const unsigned char PY_mb_li    []={"ÀåÀæÀçÀèÀéÀêÀëÀìÀíÀîÀïÀğÀñÀòÀóÀôÀõÀöÀ÷ÀøÀùÀúÀûÀüÀıÀşÁ¡Á¢Á£Á¤Á¥Á¦Á§Á¨ØªÙ³ÙµÛªÛŞÜÂİ°İñŞ¼ß¿à¦à¬áûäàå¢åÎæ²æËæêçÊèÀèİéöìåíÂíÇîºî¾ï®ğ¿ğİğßòÃòÛó»óÒóöôÏõ·õÈö¨öâ÷¯÷ó"};
const unsigned char PY_mb_lia   []={"Á©"};
const unsigned char PY_mb_lian  []={"ÁªÁ«Á¬Á­Á®Á¯Á°Á±Á²Á³Á´ÁµÁ¶Á·İüŞÆäòå¥çöé¬éçì¡ñÍñÏó¹öã"};
const unsigned char PY_mb_liang []={"Á©Á¸Á¹ÁºÁ»Á¼Á½Á¾Á¿ÁÀÁÁÁÂÜ®İ¹é£õÔ÷Ë"};
const unsigned char PY_mb_liao  []={"ÁÃÁÄÁÅÁÆÁÇÁÈÁÉÁÊÁËÁÌÁÍÁÎÁÏŞ¤ŞÍàÚâ²å¼çÔîÉğÓ"};
const unsigned char PY_mb_lie   []={"ÁĞÁÑÁÒÁÓÁÔÙıÛøŞæßÖä£ôóõñ÷à"};
const unsigned char PY_mb_lin   []={"ÁÕÁÖÁ×ÁØÁÙÁÚÁÛÁÜÁİÁŞÁßÁàİşßøá×âŞãÁåàéİê¥ì¢î¬ôÔõï÷ë"};
const unsigned char PY_mb_ling  []={"ÀâÁáÁâÁãÁäÁåÁæÁçÁèÁéÁêÁëÁìÁíÁîÛ¹ÜßßÊàòãöç±èÚèùê²ñöòÈôáöì"};
const unsigned char PY_mb_liu   []={"ÁïÁğÁñÁòÁóÁôÁõÁöÁ÷ÁøÁùÂµÂ½ä¯åŞæòç¸ì¼ìÖï³ïÖğÒöÌ"};
const unsigned char PY_mb_lo    []={"¿©"};
const unsigned char PY_mb_long  []={"ÁúÁûÁüÁıÁşÂ¡Â¢Â£Â¤ÅªÛâÜ×ãñççèĞëÊíÃñª"};
const unsigned char PY_mb_lou   []={"Â¥Â¦Â§Â¨Â©ÂªÂ¶ÙÍİäà¶áĞïÎğüñïò÷÷Ã"};
const unsigned char PY_mb_lu    []={"ÁùÂ«Â¬Â­Â®Â¯Â°Â±Â²Â³Â´ÂµÂ¶Â·Â¸Â¹ÂºÂ»Â¼Â½Â¾ÂÌÛäß£ààãòäËäõåÖè´èÓéÖéñéûê¤êÚëªëÍïåğµğØóüôµöÔ"};
const unsigned char PY_mb_luan  []={"ÂÍÂÎÂÏÂĞÂÑÂÒÙõæ®èïğ½öÇ"};
const unsigned char PY_mb_lve   []={"ÂÓÂÔï²"};
const unsigned char PY_mb_lun   []={"ÂÕÂÖÂ×ÂØÂÙÂÚÂÛàğ"};
const unsigned char PY_mb_luo   []={"¸õ¿©ÀÓÂÜÂİÂŞÂßÂàÂáÂâÂãÂäÂåÂæÂçÙÀÙùÜıŞÛŞûâ¤ãøäğçóé¡ëáíÑïİñ§öÃ"};
const unsigned char PY_mb_lv    []={"Â¿ÂÀÂÁÂÂÂÃÂÄÂÅÂÆÂÇÂÈÂÉÂÊÂËÂÌÙÍŞÛãÌéµëöïùñÚ"};
const unsigned char PY_mb_m     []={"ß¼"}; 
const unsigned char PY_mb_ma    []={"ÂèÂéÂêÂëÂìÂíÂîÂïÂğÄ¦Ä¨ßéáïæÖè¿ó¡"};
const unsigned char PY_mb_mai   []={"ÂñÂòÂóÂôÂõÂöÛ½İ¤ö²"};
const unsigned char PY_mb_man   []={"ÂñÂ÷ÂøÂùÂúÂûÂüÂıÂşÃ¡Ü¬á£çÏì×ïÜò©òı÷©÷´"};
const unsigned char PY_mb_mang  []={"Ã¢Ã£Ã¤Ã¥Ã¦Ã§ÚøäİíËòş"};
const unsigned char PY_mb_mao   []={"Ã¨Ã©ÃªÃ«Ã¬Ã­Ã®Ã¯Ã°Ã±Ã²Ã³ÙóÜâá¹ã÷è£êÄêóë£ì¸í®î¦òúó±÷Ö"};
const unsigned char PY_mb_me    []={"Ã´"};
const unsigned char PY_mb_mei   []={"ÃµÃ¶Ã·Ã¸Ã¹ÃºÃ»Ã¼Ã½Ã¾Ã¿ÃÀÃÁÃÂÃÃÃÄİ®áÒâ­ä¼äØé¹ïÑğÌñÇ÷È"};
const unsigned char PY_mb_men   []={"ÃÅÃÆÃÇŞÑìËí¯îÍ"};
const unsigned char PY_mb_meng  []={"ÃÈÃÉÃÊÃËÃÌÃÍÃÎÃÏÛÂİùŞ«ãÂëüíæòµòìó·ô»ô¿"};
const unsigned char PY_mb_mi    []={"ÃĞÃÑÃÒÃÓÃÔÃÕÃÖÃ×ÃØÃÙÃÚÃÛÃÜÃİØÂÚ¢Ú×ŞÂßäà×â¨ãèåµåôæùëßìòôÍôé÷ã÷ç"};
const unsigned char PY_mb_mian  []={"ÃŞÃßÃàÃáÃâÃãÃäÃåÃæãæäÅäÏå²ëïíí"};
const unsigned char PY_mb_miao  []={"ÃçÃèÃéÃêÃëÃìÃíÃîß÷åãç¿çÑèÂíµíğğÅ"};
const unsigned char PY_mb_mie   []={"ÃïÃğØ¿ßãóºóú"};
const unsigned char PY_mb_min   []={"ÃñÃòÃóÃôÃõÃöÜåáºãÉãıçÅçäçëíªö¼÷ª"};
const unsigned char PY_mb_ming  []={"Ã÷ÃøÃùÃúÃûÃüÚ¤ÜøäéêÔî¨õ¤"};
const unsigned char PY_mb_miu   []={"ÃıçÑ"};
const unsigned char PY_mb_mo    []={"ÂöÃ»ÃşÄ¡Ä¢Ä£Ä¤Ä¥Ä¦Ä§Ä¨Ä©ÄªÄ«Ä¬Ä­Ä®Ä¯Ä°ÍòÚÓÜÔİëâÉæÆéâïÒï÷ñ¢ñòõöõø÷á"};
const unsigned char PY_mb_mou   []={"Ä±Ä²Ä³Ù°ßèçÑíøòÖöÊ"};
const unsigned char PY_mb_mu    []={"Ä£Ä²Ä´ÄµÄ¶Ä·Ä¸Ä¹ÄºÄ»Ä¼Ä½Ä¾Ä¿ÄÀÄÁÄÂØïÛéÜÙãåë¤îâ"};
const unsigned char PY_mb_na    []={"ÄÃÄÄÄÅÄÆÄÇÄÈÄÉŞàëÇïÕñÄ"};
const unsigned char PY_mb_nai   []={"ÄÊÄËÄÌÄÍÄÎØ¾Ù¦ÜµİÁèÍ"};
const unsigned char PY_mb_nan   []={"ÄÏÄĞÄÑà«àïéªëîòïôö"};
const unsigned char PY_mb_nang  []={"ÄÒß­àìâÎêÙ"};
const unsigned char PY_mb_nao   []={"ÄÓÄÔÄÕÄÖÄ×Ø«ÛñßÎâ®è§íĞîóòÍ"};
const unsigned char PY_mb_ne    []={"ÄØÚ«ÄÄ"};
const unsigned char PY_mb_nei   []={"ÄÚÄÙ"};
const unsigned char PY_mb_nen   []={"ÄÛí¥"};
const unsigned char PY_mb_neng  []={"ÄÜ"};
const unsigned char PY_mb_ni    []={"ÄØÄİÄŞÄßÄàÄáÄâÄãÄäÄåÄæÄçÙ£Ûèâ¥âõêÇì»ìòí«íşîêöò"};
const unsigned char PY_mb_nian  []={"ÄèÄéÄêÄëÄìÄíÄîØ¥Ûşéığ¤öÓöó"};
const unsigned char PY_mb_niang []={"ÄïÄğ"};
const unsigned char PY_mb_niao  []={"ÄñÄòÜàæÕëåôÁ"};
const unsigned char PY_mb_nie   []={"ÄóÄôÄõÄöÄ÷ÄøÄùØ¿ÚíŞÁà¿ò¨ô«õæ"};
const unsigned char PY_mb_nin   []={"Äú"};
const unsigned char PY_mb_ning  []={"ÄûÄüÄıÄşÅ¡Å¢ØúßÌå¸ñ÷"};
const unsigned char PY_mb_niu   []={"Å£Å¤Å¥Å¦ŞÖáğâîæ¤"};
const unsigned char PY_mb_nong  []={"Å©ÅªÅ§Å¨Ù¯ßæ"};
const unsigned char PY_mb_nou   []={"ññ"};
const unsigned char PY_mb_nu    []={"Å«Å¬Å­åóæÀæÛæå"};
const unsigned char PY_mb_nuan  []={"Å¯"};
const unsigned char PY_mb_nuo   []={"ÄÈÅ²Å³Å´ÅµÙĞŞùßöï»"};
const unsigned char PY_mb_nv    []={"Å®í¤îÏô¬"};
const unsigned char PY_mb_nve   []={"Å°Å±"};
const unsigned char PY_mb_o     []={"Å¶à¸àŞ"};
const unsigned char PY_mb_ou    []={"Å·Å¸Å¹ÅºÅ»Å¼Å½ÇøÚ©âæê±ñî"};
const unsigned char PY_mb_pa    []={"°Ç°ÒÅ¾Å¿ÅÀÅÁÅÂÅÃİâèËóá"};
const unsigned char PY_mb_pai   []={"ÅÄÅÅÅÆÅÇÅÈÅÉÆÈÙ½İåßß"};
const unsigned char PY_mb_pan   []={"·¬ÅÊÅËÅÌÅÍÅÎÅÏÅĞÅÑÅÖŞÕãÜãİãúêÚñÈñáó´õç"};
const unsigned char PY_mb_pang  []={"°ò°õ°÷ÅÒÅÓÅÔÅÕÅÖáİäèåÌó¦"};
const unsigned char PY_mb_pao   []={"Å×ÅØÅÙÅÚÅÛÅÜÅİŞËáóâÒëãğå"};
const unsigned char PY_mb_pei   []={"ÅŞÅßÅàÅáÅâÅãÅäÅåÅæàÎàúì·ïÂõ¬ö¬"};
const unsigned char PY_mb_pen   []={"ÅçÅèäÔ"};
const unsigned char PY_mb_peng  []={"ÅéÅêÅëÅìÅíÅîÅïÅğÅñÅòÅóÅôÅõÅöÜ¡àØâñó²"};
const unsigned char PY_mb_pi    []={"±Ù·ñÅ÷ÅøÅùÅúÅûÅüÅıÅşÆ¡Æ¢Æ£Æ¤Æ¥Æ¦Æ§Æ¨Æ©Ø§ØòÚéÚğÚüÛ¯ÛÜÛıÜ±ÜÅß¨àèâÏäÄæÇç¢èÁê¶î¢î¼îëñ±ñÔñâò·òçõù"};
const unsigned char PY_mb_pian  []={"ÆªÆ«Æ¬Æ­ÚÒæéçÂêúëİôæõä±â±ã"};
const unsigned char PY_mb_piao  []={"Æ®Æ¯Æ°Æ±ÆÓØâàÑæÎæôçÎéèî©óª"};
const unsigned char PY_mb_pie   []={"Æ²Æ³Ø¯ÜÖë­"};
const unsigned char PY_mb_pin   []={"Æ´ÆµÆ¶Æ·Æ¸æ°æÉé¯êòò­"};
const unsigned char PY_mb_ping  []={"Æ¹ÆºÆ»Æ¼Æ½Æ¾Æ¿ÆÀÆÁÙ·æ³èÒöÒ·ë"};
const unsigned char PY_mb_po    []={"²´·±ÆÂÆÃÆÄÆÅÆÆÆÇÆÈÆÉÆÓØÏÚéÛ¶çêê·ë¶îÇîŞğ«óÍ"};
const unsigned char PY_mb_pou   []={"ÆÊÙöŞå"};
const unsigned char PY_mb_pu    []={"±¤±©¸¬ÆËÆÌÆÍÆÎÆÏÆĞÆÑÆÒÆÓÆÔÆÕÆÖÆ×ÆØÆÙÙéàÛäßå§è±ë«ïäïèõë"};
const unsigned char PY_mb_qi    []={"»ü¼©ÆÚÆÛÆÜÆİÆŞÆßÆàÆáÆâÆãÆäÆåÆæÆçÆèÆéÆêÆëÆìÆíÆîÆïÆğÆñÆòÆóÆôÆõÆöÆ÷ÆøÆùÆúÆûÆüÆıØ½ØÁÙ¹ÛßÜ»ÜÎÜùİÂİİŞ­àÒá¨áªãàä¿æëç²ç÷çùè½èçéÊêÈì¥ì÷í¬íÓñıòÓòàôëôìõè÷¢÷è"};
const unsigned char PY_mb_qia   []={"¿¨ÆşÇ¡Ç¢İÖñÊ÷Ä"};
const unsigned char PY_mb_qian  []={"Ç£Ç¤Ç¥Ç¦Ç§Ç¨Ç©ÇªÇ«Ç¬Ç­Ç®Ç¯Ç°Ç±Ç²Ç³Ç´ÇµÇ¶Ç·Ç¸ÏËÙ»ÙİÚäÜ·ÜÍÜçİ¡Şçá©ã¥ã»å¹åºå½ç×èıêùëÉí©îÔò¯óéôÇ"};
const unsigned char PY_mb_qiang []={"Ç¹ÇºÇ»Ç¼Ç½Ç¾Ç¿ÇÀãÜãŞæÍéÉê¨ìÁïÏïêñßòŞôÇõÄ"};
const unsigned char PY_mb_qiao  []={"¿ÇÇÁÇÂÇÃÇÄÇÅÇÆÇÇÇÈÇÉÇÊÇËÇÌÇÍÇÎÇÏÈ¸ØäÚ½ÚÛÜñá½ã¸ã¾çØéÔíÍï¢õÎ÷³"};
const unsigned char PY_mb_qie   []={"ÇĞÇÑÇÒÇÓÇÔÙ¤Û§ã«ã»æªêüïÆóæôò"};
const unsigned char PY_mb_qin   []={"ÇÕÇÖÇ×ÇØÇÙÇÚÇÛÇÜÇİÇŞÇßÜËŞìßÄàºàßâÛéÕï·ñæñûòûôÀ"};
const unsigned char PY_mb_qing  []={"Ç×ÇàÇáÇâÇãÇäÇåÇæÇçÇèÇéÇêÇëÇìÜÜàõéÑíàïºòßóÀóäôìö¥öë÷ô"};
const unsigned char PY_mb_qiong []={"ÇíÇîÚöÜäñ·òËóÌõ¼öÆ"};
const unsigned char PY_mb_qiu   []={"³ğ¹êÇïÇğÇñÇòÇóÇôÇõÇöÙ´ÛÏáìäĞåÏåÙé±êäò°òÇòøôÃôÜöú"};
const unsigned char PY_mb_qu    []={"Ç÷ÇøÇùÇúÇûÇüÇıÇşÈ¡È¢È£È¤È¥ĞçÚ°Û¾ÛÉÜÄŞ¡Ş¾á«áéãÖè³êïë¬ëÔìîíáğ¶ñ³òĞó½ôğöÄ÷ñ"};
const unsigned char PY_mb_quan  []={"È¦È§È¨È©ÈªÈ«È¬È­È®È¯È°Ú¹Üõáëãªç¹éúî°îıòéóÜ÷Ü"};
const unsigned char PY_mb_que   []={"È±È²È³È´ÈµÈ¶È·È¸ã×ãÚí¨"};
const unsigned char PY_mb_qui   []={"÷ü"};
const unsigned char PY_mb_qun   []={"È¹ÈºåÒ÷å"};
const unsigned char PY_mb_ran   []={"È»È¼È½È¾ÜÛòÅ÷×"};
const unsigned char PY_mb_rang  []={"È¿ÈÀÈÁÈÂÈÃìüğ¦"};
const unsigned char PY_mb_rao   []={"ÈÄÈÅÈÆÜéæ¬èã"};
const unsigned char PY_mb_re    []={"ÈÇÈÈßö"};
const unsigned char PY_mb_ren   []={"ÈÉÈÊÈËÈÌÈÍÈÎÈÏÈĞÈÑÈÒØéØğÜóİØâ¿éíïşñÅ"};
const unsigned char PY_mb_reng  []={"ÈÓÈÔ"};
const unsigned char PY_mb_ri    []={"ÈÕ"};
const unsigned char PY_mb_rong  []={"ÈÖÈ×ÈØÈÙÈÚÈÛÈÜÈİÈŞÈßáÉáõéÅëÀòî"};
const unsigned char PY_mb_rou   []={"ÈàÈáÈâôÛõå÷·"};
const unsigned char PY_mb_ru    []={"ÈãÈäÈåÈæÈçÈèÈéÈêÈëÈìİêŞ¸àéä²äáå¦çÈï¨ñàò¬"};
const unsigned char PY_mb_ruan  []={"ÈíÈîëÃ"};
const unsigned char PY_mb_rui   []={"ÈïÈğÈñÜÇŞ¨èÄî£ò¸"};
const unsigned char PY_mb_run   []={"ÈòÈó"};
const unsigned char PY_mb_ruo   []={"ÈôÈõÙ¼óè"};
const unsigned char PY_mb_sa    []={"ÈöÈ÷ÈøØ¦ØíëÛìª"};
const unsigned char PY_mb_sai   []={"ÈùÈúÈûÈüàç"};
const unsigned char PY_mb_san   []={"ÈıÈşÉ¡É¢âÌë§ôÖ"};
const unsigned char PY_mb_sang  []={"É£É¤É¥Şúíßòª"};
const unsigned char PY_mb_sao   []={"É¦É§É¨É©Ü£çÒëığşöş"};
const unsigned char PY_mb_se    []={"ÈûÉªÉ«É¬ØÄï¤ğ£"};
const unsigned char PY_mb_sen   []={"É­"};
const unsigned char PY_mb_seng  []={"É®"};
const unsigned char PY_mb_sha   []={"É¯É°É±É²É³É´ÉµÉ¶É·É¼ÏÃßşì¦ï¡ğğôÄö®öè"};
const unsigned char PY_mb_shai  []={"É«É¸É¹"};
const unsigned char PY_mb_shan  []={"²ôµ¥ÉºÉ»É¼É½É¾É¿ÉÀÉÁÉÂÉÃÉÄÉÅÉÆÉÇÉÈÉÉÕ¤ØßÚ¨Û·ÛïÜÏáêäúæ©æÓæóëşìøîÌğŞóµô®õÇ÷­÷Ô"};
const unsigned char PY_mb_shang []={"ÉÊÉËÉÌÉÍÉÎÉÏÉĞÉÑÛğç´éäìØõü"};
const unsigned char PY_mb_shao  []={"ÇÊÉÒÉÓÉÔÉÕÉÖÉ×ÉØÉÙÉÚÉÛÉÜÛ¿Üæäûè¼òÙóâô¹"};
const unsigned char PY_mb_she   []={"ÉİÉŞÉßÉàÉáÉâÉãÉäÉåÉæÉçÉèÕÛØÇÙÜŞéâ¦äÜì¨î´îè÷ê"};
const unsigned char PY_mb_shei  []={"Ë­"};
const unsigned char PY_mb_shen  []={"²ÎÉéÉêÉëÉìÉíÉîÉïÉğÉñÉòÉóÉôÉõÉöÉ÷ÉøÊ²Ú·ÚÅİ·İØßÓäÉé©ëÏïòò×"};
const unsigned char PY_mb_sheng []={"³ËÉùÉúÉûÉüÉıÉşÊ¡Ê¢Ê£Ê¤Ê¥áÓäÅêÉíòóÏ"};
const unsigned char PY_mb_shi   []={"³×Ê¦Ê§Ê¨Ê©ÊªÊ«Ê¬Ê­Ê®Ê¯Ê°Ê±Ê²Ê³Ê´ÊµÊ¶Ê·Ê¸Ê¹ÊºÊ»Ê¼Ê½Ê¾Ê¿ÊÀÊÁÊÂÊÃÊÄÊÅÊÆÊÇÊÈÊÉÊÊÊËÊÌÊÍÊÎÊÏÊĞÊÑÊÒÊÓÊÔËÆÖ³ÖÅÚÖÛõİªİéß±â»éøêÛìÂìêîæîèó§óÂóßõ§õ¹öåöõ"};
const unsigned char PY_mb_shou  []={"ÊÕÊÖÊ×ÊØÊÙÊÚÊÛÊÜÊİÊŞŞĞá÷ç·ô¼"};
const unsigned char PY_mb_shu   []={"ÊßÊàÊáÊâÊãÊäÊåÊæÊçÊèÊéÊêÊëÊìÊíÊîÊïÊğÊñÊòÊóÊôÊõÊöÊ÷ÊøÊùÊúÊûÊüÊıÊşË¡Ø­Ù¿ÛÓİÄŞóãğäøæ­ç£ë¨ëòì¯ïíïøñâ"};
const unsigned char PY_mb_shua  []={"Ë¢Ë£à§"};
const unsigned char PY_mb_shuai []={"ÂÊË¤Ë¥Ë¦Ë§ó°"};
const unsigned char PY_mb_shuan []={"Ë¨Ë©ãÅäÌ"};
const unsigned char PY_mb_shuang[]={"ËªË«Ë¬ãñæ×"};
const unsigned char PY_mb_shui  []={"Ë­Ë®Ë¯Ë°Ëµãß"};
const unsigned char PY_mb_shun  []={"Ë±Ë²Ë³Ë´"};
const unsigned char PY_mb_shuo  []={"ÊıËµË¶Ë·Ë¸İôŞ÷åùéÃîå"};
const unsigned char PY_mb_si    []={"Ë¹ËºË»Ë¼Ë½Ë¾Ë¿ËÀËÁËÂËÃËÄËÅËÆËÇËÈØËÙ¹ÙîÛÌßĞâ»ãáãôäùæ¦æáçÁìëïÈğ¸ñêòÏóÓ"};
const unsigned char PY_mb_song  []={"ËÉËÊËËËÌËÍËÎËÏËĞÚ¡İ¿áÂáÔâìã¤äÁñµ"};
const unsigned char PY_mb_sou   []={"ËÑËÒËÓËÔÛÅŞ´à²àÕâÈäÑì¬î¤ïËòô"};
const unsigned char PY_mb_su    []={"ËÕËÖË×ËØËÙËÚËÛËÜËİËŞËßËàËõÙíÚÕİøà¼ãºä³óùö¢öÕ"};
const unsigned char PY_mb_suan  []={"ËáËâËãâ¡"};
const unsigned char PY_mb_sui   []={"ËäËåËæËçËèËéËêËëËìËíËîÚÇİ´å¡åäìİíõî¡Äò"};
const unsigned char PY_mb_sun   []={"ËïËğËñİ¥áøâ¸é¾öÀ"};
const unsigned char PY_mb_suo   []={"ËòËóËôËõËöË÷ËøËùßïàÂàÊæ¶èøêıíüôÈÉ¯"};
const unsigned char PY_mb_ta    []={"ËúËûËüËıËşÌ¡Ì¢Ì£Ì¤ÍØãËäâäğåİé½í³îèõÁ÷£"};
const unsigned char PY_mb_tai   []={"Ì¥Ì¦Ì§Ì¨Ì©ÌªÌ«Ì¬Ì­Û¢Ş·ææëÄìÆîÑõÌöØ"};
const unsigned char PY_mb_tan   []={"µ¯Ì®Ì¯Ì°Ì±Ì²Ì³Ì´ÌµÌ¶Ì·Ì¸Ì¹ÌºÌ»Ì¼Ì½Ì¾Ì¿Û°å£ê¼êæìşîãïÄïâñû"};
const unsigned char PY_mb_tang  []={"ÌÀÌÁÌÂÌÃÌÄÌÅÌÆÌÇÌÈÌÉÌÊÌËÌÌÙÎàûâ¼äçè©éÌîõï¦ïÛñíó¥ó«ôÊõ±"};
const unsigned char PY_mb_tao   []={"ÌÍÌÎÌÏÌĞÌÑÌÒÌÓÌÔÌÕÌÖÌ×Ø»ß¶ßûä¬èºìâ÷Ò"};
const unsigned char PY_mb_te    []={"ÌØß¯ìıï«"};
const unsigned char PY_mb_teng  []={"ÌÙÌÚÌÛÌÜëø"};
const unsigned char PY_mb_ti    []={"ÌİÌŞÌßÌàÌáÌâÌãÌäÌåÌæÌçÌèÌéÌêÌëÙÃÜèã©åÑç°ç¾ğÃñÓõ®"};
const unsigned char PY_mb_tian  []={"ÌìÌíÌîÌïÌğÌñÌòÌóŞİãÃãÙéåî±îäï»"};
const unsigned char PY_mb_tiao  []={"µ÷ÌôÌõÌöÌ÷ÌøÙ¬Üæìöï¢ñ»òèóÔôĞö¶öæ÷Ø"};
const unsigned char PY_mb_tie   []={"ÌùÌúÌûİÆï°÷Ñ"};
const unsigned char PY_mb_ting  []={"ÌüÌıÌşÍ¡Í¢Í£Í¤Í¥Í¦Í§ÜğİãæÃèèîúòÑöª"};
const unsigned char PY_mb_tong  []={"Í¨Í©ÍªÍ«Í¬Í­Í®Í¯Í°Í±Í²Í³Í´Ù¡Ù×ÙÚÛíÜíàÌá¼âúäüíÅ"};
const unsigned char PY_mb_tou   []={"ÍµÍ¶Í·Í¸Ùïî×÷»"};
const unsigned char PY_mb_tu    []={"Í¹ÍºÍ»Í¼Í½Í¾Í¿ÍÀÍÁÍÂÍÃÜ¢İ±İËîÊõ©"};
const unsigned char PY_mb_tuan  []={"ÍÄÍÅŞÒåèî¶"};
const unsigned char PY_mb_tui   []={"ÍÆÍÇÍÈÍÉÍÊÍËìÕ"};
const unsigned char PY_mb_tun   []={"¶ÚÍÊÍÌÍÍÍÎÙÛâ½êÕëà"};
const unsigned char PY_mb_tuo   []={"ÍÏÍĞÍÑÍÒÍÓÍÔÍÕÍÖÍ×ÍØÍÙØ±Ù¢ÛçâÕãûèØèŞéÒíÈîèóêõ¢õÉö¾Ëµ"};
const unsigned char PY_mb_wa    []={"ÍÚÍÛÍÜÍİÍŞÍßÍàØôæ´ëğ"};
const unsigned char PY_mb_wai   []={"ÍáÍâáË"};
const unsigned char PY_mb_wan   []={"ÍãÍäÍåÍæÍçÍèÍéÍêÍëÍìÍíÍîÍïÍğÍñÍòÍóØàÂûÜ¹İ¸İÒæıçºçşëäîµòê÷´"};
const unsigned char PY_mb_wang  []={"ÍôÍõÍöÍ÷ÍøÍùÍúÍûÍüÍıØèŞÌã¯éş÷Í"};
const unsigned char PY_mb_wei   []={"ÍşÎ¡Î¢Î£Î¤Î¥Î¦Î§Î¨Î©ÎªÎ«Î¬Î­Î®Î¯Î°Î±Î²Î³Î´ÎµÎ¶Î·Î¸Î¹ÎºÎ»Î¼Î½Î¾Î¿ÎÀÙËÚÃÚñÚóÛ×İÚŞ±àíàøá¡áËáÍâ«â¬ãÇãíä¢ä¶åÔæ¸çâè¸ê¦ì¿ìĞğôôºöÛ"};
const unsigned char PY_mb_wen   []={"ÎÁÎÂÎÃÎÄÎÅÎÆÎÇÎÈÎÉÎÊØØãÓãëçäè·ö©"};
const unsigned char PY_mb_weng  []={"ÎËÎÌÎÍİîŞ³"};
const unsigned char PY_mb_wo    []={"ÎÒÎÎÎÏÎĞÎÑÎÓÎÔÎÕÎÖÙÁİ«à¸á¢ä×ë¿íÒö»"};
const unsigned char PY_mb_wu    []={"¶ñÎ×ÎØÎÙÎÚÎÛÎÜÎİÎŞÎßÎàÎáÎâÎãÎäÎåÎæÎçÎèÎéÎêÎëÎìÎíÎîÎïÎğÎñÎòÎóØ£ØõÚãÚùÛØÜÌßíâĞâäâèä´å»åÃåüæÄæğè»êõì¶ìÉğÄğÍğíòÚöÈ÷ù"};
const unsigned char PY_mb_xi    []={"ÎôÎõÎöÎ÷ÎøÎùÎúÎûÎüÎıÎşÏ¡Ï¢Ï£Ï¤Ï¥Ï¦Ï§Ï¨Ï©ÏªÏ«Ï¬Ï­Ï®Ï¯Ï°Ï±Ï²Ï³Ï´ÏµÏ¶Ï·Ï¸ØÎÙÒÙâÚôÛ­Üçİ¾İßİûŞÉßñáãâ¾ãÒä»äÀåïæÒçôéØêØêêì¤ì¨ìäìùìûğªñ¶ñÓòáó£ó¬ôªô¸ôËôÑôâõµõè÷û"};
const unsigned char PY_mb_xia   []={"Ï¹ÏºÏ»Ï¼Ï½Ï¾Ï¿ÏÀÏÁÏÂÏÃÏÄÏÅßÈáòåÚè¦èÔíÌóÁ÷ï"};
const unsigned char PY_mb_xian  []={"Ï³Ï´ÏÆÏÇÏÈÏÉÏÊÏËÏÌÏÍÏÎÏÏÏĞÏÑÏÒÏÓÏÔÏÕÏÖÏ×ÏØÏÙÏÚÏÛÏÜÏİÏŞÏßÙşÜÈİ²Şºá­áıåßæµë¯ìŞììğÂğçğïò¹óÚôÌõ£õĞõÑö±"};
const unsigned char PY_mb_xiang []={"ÏàÏáÏâÏãÏäÏåÏæÏçÏèÏéÏêÏëÏìÏíÏîÏïÏğÏñÏòÏóÜ¼İÙâÃâÔæøç½ó­öß÷Ï½µ"};
const unsigned char PY_mb_xiao  []={"ÏôÏõÏöÏ÷ÏøÏùÏúÏûÏüÏıÏşĞ¡Ğ¢Ğ£Ğ¤Ğ¥Ğ¦Ğ§ßØäìåĞæçç¯èÉèÕòÙóãóï÷Ì"};
const unsigned char PY_mb_xie   []={"½âĞ¨Ğ©ĞªĞ«Ğ¬Ğ­Ğ®Ğ¯Ğ°Ğ±Ğ²Ğ³Ğ´ĞµĞ¶Ğ·Ğ¸Ğ¹ĞºĞ»Ğ¼ÑªÒ¶ÙÉÙôÛÄÛÆŞ¯ß¢â³âİäÍå¬åâç¥çÓé¿éÇò¡õóöÙ÷º"};
const unsigned char PY_mb_xin   []={"Ğ½Ğ¾Ğ¿ĞÀĞÁĞÂĞÃĞÄĞÅĞÆØ¶Ü°İ·âàê¿ì§ïâöÎ"};
const unsigned char PY_mb_xing  []={"Ê¡ĞÇĞÈĞÉĞÊĞËĞÌĞÍĞÎĞÏĞĞĞÑĞÒĞÓĞÔĞÕÚêÜôÜşß©â¼ã¬íÊ"};
const unsigned char PY_mb_xiong []={"ĞÖĞ×ĞØĞÙĞÚĞÛĞÜÜº"};
const unsigned char PY_mb_xiu   []={"³ôËŞĞİĞŞĞßĞàĞáĞâĞãĞäĞåßİá¶âÊâÓäåğ¼õ÷÷Û"};
const unsigned char PY_mb_xu    []={"ĞæĞçĞèĞéĞêĞëĞìĞíĞîĞïĞğĞñĞòĞóĞôĞõĞöĞ÷ĞøÓõÚ¼ÛÃÛ×Ş£äªä°äÓçïèòìãíìñãôÚõ¯"};
const unsigned char PY_mb_xuan  []={"ĞùĞúĞûĞüĞıĞşÑ¡Ñ¢Ñ£Ñ¤ÙØÚÎİæŞïãùäÖäöè¯é¸êÑìÅìÓíÛîçïàÈ¯"};
const unsigned char PY_mb_xue   []={"Ñ¥Ñ¦Ñ§Ñ¨Ñ©ÑªÚÊàåí´õ½÷¨Ï÷"};
const unsigned char PY_mb_xun   []={"¿£Ñ«Ñ¬Ñ­Ñ®Ñ¯Ñ°Ñ±Ñ²Ñ³Ñ´ÑµÑ¶Ñ·Ñ¸ÙãÛ¨Û÷Ü÷İ¡Ş¦Ş¹á¾áßâ´âşä­ä±êÖñ¿õ¸öà"};
const unsigned char PY_mb_ya    []={"Ñ¹ÑºÑ»Ñ¼Ñ½Ñ¾Ñ¿ÑÀÑÁÑÂÑÃÑÄÑÅÑÆÑÇÑÈÔşØóÛëŞëá¬åÂæ«çğèâë²í¼íığéñâ"};
const unsigned char PY_mb_yan   []={"ÑÉÑÊÑËÑÌÑÍÑÎÑÏÑĞÑÑÑÒÑÓÑÔÑÕÑÖÑ×ÑØÑÙÑÚÑÛÑÜÑİÑŞÑßÑàÑáÑâÑãÑäÑåÑæÑçÑèÑéÒóØÉØÍØßÙ²ÙÈÙğÚ¥ÚİÚçÛ±Û³Ü¾İÎáÃâûãÆãÕäÎäÙåûæÌçüéÜêÌëÙëçìÍî»óÛõ¦÷Ê÷Ğ÷ú÷üÇ¦"};
const unsigned char PY_mb_yang  []={"ÑòÑóÑôÑõÑöÑêÑëÑìÑíÑîÑïÑğÑñÑ÷ÑøÑùÑúáàâóãóì¾ìÈí¦òÕ÷±"};
const unsigned char PY_mb_yao   []={"½ÄÄöÅ±ÑûÑüÑıÑşÒ¡Ò¢Ò£Ò¤Ò¥Ò¦Ò§Ò¨Ò©ÒªÒ«Ô¿Ø²Ø³ßºáÅáÊáæçÛçòèÃé÷ê×ëÈï¢ğÎñºôí÷¥"};
const unsigned char PY_mb_ye    []={"ÑÊÒ¬Ò­Ò®Ò¯Ò°Ò±Ò²Ò³Ò´ÒµÒ¶Ò·Ò¸Ò¹ÒºÖÑØÌÚËÚşŞŞçğêÊìÇîôĞ°"};
const unsigned char PY_mb_yi    []={"°¬Î²Ò»Ò¼Ò½Ò¾Ò¿ÒÀÒÁÒÂÒÃÒÄÒÅÒÆÒÇÒÈÒÉÒÊÒËÒÌÒÍÒÎÒÏÒĞÒÑÒÒÒÓÒÔÒÕÒÖÒ×ÒØÒÙÒÚÒÛÒÜÒİÒŞÒßÒàÒáÒâÒãÒäÒåÒæÒçÒèÒéÒêÒëÒìÒíÒîÒïØ×ØæØıÙ«Ú±ÚâÛİÛüÜ²ÜÓÜèŞ²ŞÄŞÈŞÚß®ß½ß×ßŞàæá»áÚâ¢âÂâøâùã¨äôåÆæäçËéìéóêİì¥ì½ìÚíôîÆîèï×ïîğêğùñ¯ñ´ñÂòæô¯ôàôèôı÷ğ"};
const unsigned char PY_mb_yin   []={"ÒğÒñÒòÒóÒôÒõÒöÒ÷ÒøÒùÒúÒûÒüÒıÒşÓ¡Ø·Û´ÛÈÛóÜ§ÜáßÅà³áşâ¹ä¦äÎë³î÷ñ«ñ¿ò¾ö¯ö¸"};
const unsigned char PY_mb_ying  []={"Ó¢Ó£Ó¤Ó¥Ó¦Ó§Ó¨Ó©ÓªÓ«Ó¬Ó­Ó®Ó¯Ó°Ó±Ó²Ó³ÙøÛ«ÜãÜşİºİÓİöŞüàÓâßäŞäëå­çøè¬éºëôğĞñ¨ò£ó¿"};
const unsigned char PY_mb_yo    []={"Ó´Óıà¡"};
const unsigned char PY_mb_yong  []={"ÓµÓ¶Ó·Ó¸Ó¹ÓºÓ»Ó¼Ó½Ó¾Ó¿ÓÀÓÁÓÂÓÃÙ¸ÛÕÜ­à¯ã¼çßïŞğ®÷«÷Ó"};
const unsigned char PY_mb_you   []={"ÓÄÓÅÓÆÓÇÓÈÓÉÓÊÓËÓÌÓÍÓÎÓÏÓĞÓÑÓÒÓÓÓÔÓÕÓÖÓ×ØÕØüÙ§İ¬İ¯İµŞÌßÏàóå¶èÖéàë»îğğàòÄòÊòöòøôíöÏ÷î÷ø"};
const unsigned char PY_mb_yu    []={"ÎµÎ¾ÓØÓÙÓÚÓÛÓÜÓİÓŞÓßÓàÓáÓâÓãÓäÓåÓæÓçÓèÓéÓêÓëÓìÓíÓîÓïÓğÓñÓòÓóÓôÓõÓöÓ÷ÓøÓùÓúÓûÓüÓıÓşÔ¡Ô¢Ô£Ô¤Ô¥Ô¦Ø®Ø¹ØñÙ¶ÚÄÚÍİÇİÒİ÷ŞíàôàöáÎáüâÀâÅâ×ãĞå÷åıæ¥æúè¤êÅêìëéì£ì¶ìÏìÙìÛí±í²îÚğÁğÖğõğöñ¾ñÁòâòõóÄô§ô¨ö§ö¹"};
const unsigned char PY_mb_yuan  []={"Ô§Ô¨Ô©ÔªÔ«Ô¬Ô­Ô®Ô¯Ô°Ô±Ô²Ô³Ô´ÔµÔ¶Ô·Ô¸Ô¹ÔºÜ«Ü¾Şòà÷ãäæÂè¥éÚë¼íóğ°ó¢óîö½"};
const unsigned char PY_mb_yue   []={"Ô»Ô¼Ô½Ô¾Ô¿ÔÀÔÁÔÂÔÃÔÄÙßßÜå®èİéĞë¾îáÀÖËµ"};
const unsigned char PY_mb_yun   []={"ÔÅÔÆÔÇÔÈÔÉÔÊÔËÔÌÔÍÔÎÔÏÔĞÛ©Ü¿áñã¢ã³ç¡è¹éæêÀëµìÙóŞÔ±"};
const unsigned char PY_mb_za    []={"ÔÑÔÒÔÓÔúÕ¦ŞÙßÆ"};
const unsigned char PY_mb_zai   []={"ÔÔÔÕÔÖÔ×ÔØÔÙÔÚáÌçŞ"};
const unsigned char PY_mb_zan   []={"ÔÛÔÜÔİÔŞŞÙè¶êÃô¢ôØôõöÉ"};
const unsigned char PY_mb_zang  []={"²ØÔßÔàÔáæàê°"};
const unsigned char PY_mb_zao   []={"ÔâÔãÔäÔåÔæÔçÔèÔéÔêÔëÔìÔíÔîÔïßğ"};
const unsigned char PY_mb_ze    []={"ÔğÔñÔòÔóÕ¦ØÆØÓßõàıåÅê¾óĞóåô·"};
const unsigned char PY_mb_zei   []={"Ôô"};
const unsigned char PY_mb_zen   []={"ÔõÚÚ"};
const unsigned char PY_mb_zeng  []={"ÔöÔ÷ÔøÔùçÕêµîÀï­"};
const unsigned char PY_mb_zha   []={"²éÔúÔûÔüÔıÔşÕ¡Õ¢Õ£Õ¤Õ¥Õ¦Õ§Õ¨Õ©×õŞêß¸ßåßîà©é«íÄğäòÆö´÷ş"};
const unsigned char PY_mb_zhai  []={"µÔÔñÕªÕ«Õ¬Õ­Õ®Õ¯íÎñ©"};
const unsigned char PY_mb_zhan  []={"²üÕ°Õ±Õ²Õ³Õ´ÕµÕ¶Õ·Õ¸Õ¹ÕºÕ»Õ¼Õ½Õ¾Õ¿ÕÀÚŞŞøæöì¹"};
const unsigned char PY_mb_zhang []={"³¤ÕÁÕÂÕÃÕÄÕÅÕÆÕÇÕÈÕÉÕÊÕËÕÌÕÍÕÎÕÏØëÛµá¤áÖâ¯æÑè°ó¯"};
const unsigned char PY_mb_zhao  []={"³¯ÕĞÕÑÕÒÕÓÕÔÕÕÕÖÕ×ÕØÕÙ×¦×ÅÚ¯ßúèşîÈóÉ"};
const unsigned char PY_mb_zhe   []={"ÕÚÕÛÕÜÕİÕŞÕßÕàÕáÕâÕã×ÅÚØß¡èÏéüíİğÑñŞòØô÷"};
const unsigned char PY_mb_zhen  []={"ÕäÕåÕæÕçÕèÕéÕêÕëÕìÕíÕîÕïÕğÕñÕòÕóÖ¡ÛÚİèä¥äÚçÇèåé©é»éôêâëÓëŞìõî³ğ¡ğ²óğ"};
const unsigned char PY_mb_zheng []={"ÕôÕõÕöÕ÷ÕøÕùÕúÕûÕüÕıÕşÖ¢Ö£Ö¤Úºá¿áçîÛï£óİöë"};
const unsigned char PY_mb_zhi   []={"Ê¶Ö¥Ö¦Ö§Ö¨Ö©ÖªÖ«Ö¬Ö­Ö®Ö¯Ö°Ö±Ö²Ö³Ö´ÖµÖ¶Ö·Ö¸Ö¹ÖºÖ»Ö¼Ö½Ö¾Ö¿ÖÀÖÁÖÂÖÃÖÄÖÅÖÆÖÇÖÈÖÉÖÊÖËÖÌÖÍÖÎÖÏØ´ÚìÛ¤ÛúÜÆŞıàùáçâºâååéåëæïèÎè×èÙèäéòéùêŞëÕëùìíìóíéïôğºğëòÎôêõ¥õÅõÙõÜõôö£"};
const unsigned char PY_mb_zhong []={"ÖĞÖÑÖÒÖÓÖÔÖÕÖÖÖ×ÖØÖÙÖÚÚ£âìïñó®ô±õà"};
const unsigned char PY_mb_zhou  []={"ÖÛÖÜÖİÖŞÖßÖàÖáÖâÖãÖäÖåÖæÖçÖèİ§ßúæ¨æûç§ëĞíØô¦ôíôü"};
const unsigned char PY_mb_zhu   []={"ÊôÊõÖéÖêÖëÖìÖíÖîÖïÖğÖñÖòÖóÖôÖõÖöÖ÷ÖøÖùÖúÖûÖüÖıÖş×¡×¢×£×¤Ø¼ØùÙªÛ¥ÜÑÜïä¨ä¾äóèÌéÆéÍìÄîùğæğññÒóÃóçô¶ôãõî÷æ"};
const unsigned char PY_mb_zhua  []={"ÎÎ×¥×¦"};
const unsigned char PY_mb_zhuai []={"×§×ª"};
const unsigned char PY_mb_zhuan []={"´«×¨×©×ª×«×¬×­ßùâÍãçò§"};
const unsigned char PY_mb_zhuang[]={"´±×®×¯×°×±×²×³×´ŞÊí°"};
const unsigned char PY_mb_zhui  []={"×µ×¶×·×¸×¹×ºã·æíçÄö¿"};
const unsigned char PY_mb_zhun  []={"×»×¼â½ëÆñ¸"};
const unsigned char PY_mb_zhuo  []={"×½×¾×¿×À×Á×Â×Ã×Ä×Å×Æ×ÇÙ¾ÚÂßªä·äÃåªìÌìúí½ïí"};
const unsigned char PY_mb_zi    []={"Ö¨×È×É×Ê×Ë×Ì×Í×Î×Ï×Ğ×Ñ×Ò×Ó×Ô×Õ×ÖÚÑÜëáÑæ¢æÜç»è÷ê¢êßí§íöïÅïöñèóÊôÒôôõşö¤ö·öö÷Ú"};
const unsigned char PY_mb_zong  []={"×××Ø×Ù×Ú×Û×Ü×İÙÌèÈëêôÕ"};
const unsigned char PY_mb_zou   []={"×Ş×ß×à×áÚÁÚîÛ¸æãöí"};
const unsigned char PY_mb_zu    []={"×â×ã×ä×å×æ×ç×è×éÙŞİÏïß"};
const unsigned char PY_mb_zuan  []={"×ê×ëß¬çÚõò"};
const unsigned char PY_mb_zui   []={"×ì×í×î×ïŞ©õş"};
const unsigned char PY_mb_zun   []={"×ğ×ñß¤é×÷®"};
const unsigned char PY_mb_zuo   []={"´é×Á×ò×ó×ô×õ×ö×÷×ø×ùÚèßòàÜâôëÑìñíÄõ¡"};

//**********************************************************************************************

/*"Æ´ÒôÊäÈë·¨²éÑ¯Âë±í,T9Êı×Ö×ÖÄ¸Ë÷Òı±í(index)"*/ 
t9PINYIN_INDEX  t9PinYin_Index2[]={ //--{"","",(pInt8U)PY_mb_space},//PY_mb_spaceÎª¿Õ
                                    {"2","a",(pInt8U)PY_mb_a},
                                    {"3","e",(pInt8U)PY_mb_e},
                                   //-- {"","i",(pInt8U)PY_mb_space},//PY_mb_spaceÎª¿Õ
                                    {"6","o",(pInt8U)PY_mb_o},
                                  //---  {"","u",(pInt8U)PY_mb_space},//PY_mb_spaceÎª¿Õ
                                 //--   {"","v",(pInt8U)PY_mb_space},//PY_mb_spaceÎª¿Õ
                                    {"24","ai",(pInt8U)PY_mb_ai},
                                    {"26","an",(pInt8U)PY_mb_an},
                                    {"26","ao",(pInt8U)PY_mb_ao},
                                    {"22","ba",(pInt8U)PY_mb_ba},
                                    {"24","bi",(pInt8U)PY_mb_bi},
                                    {"26","bo",(pInt8U)PY_mb_bo},
                                    {"28","bu",(pInt8U)PY_mb_bu},
                                    {"22","ca",(pInt8U)PY_mb_ca},
                                    {"23","ce",(pInt8U)PY_mb_ce},
                                    {"24","ci",(pInt8U)PY_mb_ci},
                                    {"28","cu",(pInt8U)PY_mb_cu},
                                    {"32","da",(pInt8U)PY_mb_da},
                                    {"33","de",(pInt8U)PY_mb_de},
                                    {"34","di",(pInt8U)PY_mb_di},
                                    {"38","du",(pInt8U)PY_mb_du},
                                    {"36","en",(pInt8U)PY_mb_en},
                                    {"37","er",(pInt8U)PY_mb_er},
                                    {"32","fa",(pInt8U)PY_mb_fa},
                                    {"36","fo",(pInt8U)PY_mb_fo},
                                    {"38","fu",(pInt8U)PY_mb_fu},
                                    {"42","ha",(pInt8U)PY_mb_ha},
                                    {"42","ga",(pInt8U)PY_mb_ga},
                                    {"43","ge",(pInt8U)PY_mb_ge},
                                    {"43","he",(pInt8U)PY_mb_he},
                                    {"48","gu",(pInt8U)PY_mb_gu},
                                    {"48","hu",(pInt8U)PY_mb_hu},
                                    {"54","ji",(pInt8U)PY_mb_ji},
                                    {"58","ju",(pInt8U)PY_mb_ju},
                                    {"52","ka",(pInt8U)PY_mb_ka},
                                    {"53","ke",(pInt8U)PY_mb_ke},
                                    {"58","ku",(pInt8U)PY_mb_ku},
                                    {"52","la",(pInt8U)PY_mb_la},
                                    {"53","le",(pInt8U)PY_mb_le},
                                    {"54","li",(pInt8U)PY_mb_li},
                                    {"58","lu",(pInt8U)PY_mb_lu},
                                    {"58","lv",(pInt8U)PY_mb_lv},
                                    {"62","ma",(pInt8U)PY_mb_ma},
                                    {"63","me",(pInt8U)PY_mb_me},
                                    {"64","mi",(pInt8U)PY_mb_mi},
                                    {"66","mo",(pInt8U)PY_mb_mo},
                                    {"68","mu",(pInt8U)PY_mb_mu},
                                    {"62","na",(pInt8U)PY_mb_na},
                                    {"63","ne",(pInt8U)PY_mb_ne},
                                    {"64","ni",(pInt8U)PY_mb_ni},
                                    {"68","nu",(pInt8U)PY_mb_nu},
                                    {"68","nv",(pInt8U)PY_mb_nv},
                                    {"68","ou",(pInt8U)PY_mb_ou},
                                    {"72","pa",(pInt8U)PY_mb_pa},
                                    {"74","pi",(pInt8U)PY_mb_pi},
                                    {"76","po",(pInt8U)PY_mb_po},
                                    {"78","pu",(pInt8U)PY_mb_pu},
                                    {"74","qi",(pInt8U)PY_mb_qi},
                                    {"78","qu",(pInt8U)PY_mb_qu},
                                    {"73","re",(pInt8U)PY_mb_re},
                                    {"74","ri",(pInt8U)PY_mb_ri},
                                    {"78","ru",(pInt8U)PY_mb_ru},
                                    {"72","sa",(pInt8U)PY_mb_sa},
                                    {"73","se",(pInt8U)PY_mb_se},
                                    {"74","si",(pInt8U)PY_mb_si},
                                    {"78","su",(pInt8U)PY_mb_su},
                                    {"82","ta",(pInt8U)PY_mb_ta},
                                    {"83","te",(pInt8U)PY_mb_te},
                                    {"84","ti",(pInt8U)PY_mb_ti},
                                    {"88","tu",(pInt8U)PY_mb_tu},
                                    {"92","wa",(pInt8U)PY_mb_wa},
                                    {"96","wo",(pInt8U)PY_mb_wo},
                                    {"98","wu",(pInt8U)PY_mb_wu},
                                    {"94","xi",(pInt8U)PY_mb_xi},
                                    {"98","xu",(pInt8U)PY_mb_xu},
                                    {"92","ya",(pInt8U)PY_mb_ya},
                                    {"93","ye",(pInt8U)PY_mb_ye},
                                    {"94","yi",(pInt8U)PY_mb_yi},
                                    {"96","yo",(pInt8U)PY_mb_yo},
                                    {"98","yu",(pInt8U)PY_mb_yu},
                                    {"92","za",(pInt8U)PY_mb_za},
                                    {"93","ze",(pInt8U)PY_mb_ze},
                                    {"94","zi",(pInt8U)PY_mb_zi},
                                    {"98","zu",(pInt8U)PY_mb_zu},
                                    {"264","ang",(pInt8U)PY_mb_ang},
                                    {"224","bai",(pInt8U)PY_mb_bai},
                                    {"226","ban",(pInt8U)PY_mb_ban},
                                    {"226","bao",(pInt8U)PY_mb_bao},
                                    {"234","bei",(pInt8U)PY_mb_bei},
                                    {"236","ben",(pInt8U)PY_mb_ben},
                                    {"243","bie",(pInt8U)PY_mb_bie},
                                    {"246","bin",(pInt8U)PY_mb_bin},
                                    {"224","cai",(pInt8U)PY_mb_cai},
                                    {"226","can",(pInt8U)PY_mb_can},
                                    {"226","cao",(pInt8U)PY_mb_cao},
                                    {"242","cha",(pInt8U)PY_mb_cha},
                                    {"243","che",(pInt8U)PY_mb_che},
                                    {"244","chi",(pInt8U)PY_mb_chi},
                                    {"248","chu",(pInt8U)PY_mb_chu},
                                    {"268","cou",(pInt8U)PY_mb_cou},
                                    {"284","cui",(pInt8U)PY_mb_cui},
                                    {"286","cun",(pInt8U)PY_mb_cun},
                                    {"286","cuo",(pInt8U)PY_mb_cuo},
                                    {"324","dai",(pInt8U)PY_mb_dai},
                                    {"326","dan",(pInt8U)PY_mb_dan},
                                    {"326","dao",(pInt8U)PY_mb_dao},
                                    {"343","die",(pInt8U)PY_mb_die},
                                    {"348","diu",(pInt8U)PY_mb_diu},
                                    {"368","dou",(pInt8U)PY_mb_dou},
                                    {"384","dui",(pInt8U)PY_mb_dui},
                                    {"386","dun",(pInt8U)PY_mb_dun},
                                    {"386","duo",(pInt8U)PY_mb_duo},
                                    {"326","fan",(pInt8U)PY_mb_fan},
                                    {"334","fei",(pInt8U)PY_mb_fei},
                                    {"336","fen",(pInt8U)PY_mb_fen},
                                    {"368","fou",(pInt8U)PY_mb_fou},
                                    {"424","gai",(pInt8U)PY_mb_gai},
                                    {"426","gan",(pInt8U)PY_mb_gan},
                                    {"426","gao",(pInt8U)PY_mb_gao},
                                    {"434","gei",(pInt8U)PY_mb_gei},
                                    {"436","gen",(pInt8U)PY_mb_gan},
                                    {"468","gou",(pInt8U)PY_mb_gou},
                                    {"482","gua",(pInt8U)PY_mb_gua},
                                    {"484","gui",(pInt8U)PY_mb_gui},
                                    {"486","gun",(pInt8U)PY_mb_gun},
                                    {"486","guo",(pInt8U)PY_mb_guo},
                                    {"423","hai",(pInt8U)PY_mb_hai},
                                    {"426","han",(pInt8U)PY_mb_han},
                                    {"426","hao",(pInt8U)PY_mb_hao},
                                    {"434","hei",(pInt8U)PY_mb_hei},
                                    {"436","hen",(pInt8U)PY_mb_hen},
                                    {"468","hou",(pInt8U)PY_mb_hou},
                                    {"482","hua",(pInt8U)PY_mb_hua},
                                    {"484","hui",(pInt8U)PY_mb_hui},
                                    {"486","hun",(pInt8U)PY_mb_hun},
                                    {"486","huo",(pInt8U)PY_mb_huo},
                                    {"542","jia",(pInt8U)PY_mb_jia},
                                    {"543","jie",(pInt8U)PY_mb_jie},
                                    {"546","jin",(pInt8U)PY_mb_jin},
                                    {"548","jiu",(pInt8U)PY_mb_jiu},
                                    {"583","jue",(pInt8U)PY_mb_jue},
                                    {"586","jun",(pInt8U)PY_mb_jun},
                                    {"524","kai",(pInt8U)PY_mb_kai},
                                    {"526","kan",(pInt8U)PY_mb_kan},
                                    {"526","kao",(pInt8U)PY_mb_kao},
                                    {"536","ken",(pInt8U)PY_mb_ken},
                                    {"568","kou",(pInt8U)PY_mb_kou},
                                    {"582","kua",(pInt8U)PY_mb_kua},
                                    {"584","kui",(pInt8U)PY_mb_kui},
                                    {"586","kun",(pInt8U)PY_mb_kun},
                                    {"586","kuo",(pInt8U)PY_mb_kuo},
                                    {"524","lai",(pInt8U)PY_mb_lai},
                                    {"526","lan",(pInt8U)PY_mb_lan},
                                    {"526","lao",(pInt8U)PY_mb_lao},
                                    {"534","lei",(pInt8U)PY_mb_lei},
                                    {"543","lie",(pInt8U)PY_mb_lie},
                                    {"546","lin",(pInt8U)PY_mb_lin},
                                    {"548","liu",(pInt8U)PY_mb_liu},
                                    {"568","lou",(pInt8U)PY_mb_lou},
                                    {"583","lue",(pInt8U)PY_mb_lve},
                                    {"586","lun",(pInt8U)PY_mb_lun},
                                    {"586","luo",(pInt8U)PY_mb_luo},
                                    {"624","mai",(pInt8U)PY_mb_mai},
                                    {"626","man",(pInt8U)PY_mb_man},
                                    {"626","mao",(pInt8U)PY_mb_mao},
                                    {"634","mei",(pInt8U)PY_mb_mei},
                                    {"636","men",(pInt8U)PY_mb_men},
                                    {"643","mie",(pInt8U)PY_mb_mie},
                                    {"646","min",(pInt8U)PY_mb_min},
                                    {"648","miu",(pInt8U)PY_mb_miu},
                                    {"668","mou",(pInt8U)PY_mb_mou},
                                    {"624","nai",(pInt8U)PY_mb_nai},
                                    {"626","nan",(pInt8U)PY_mb_nan},
                                    {"626","nao",(pInt8U)PY_mb_nao},
                                    {"634","nei",(pInt8U)PY_mb_nei},
                                    {"636","nen",(pInt8U)PY_mb_nen},
                                    {"643","nie",(pInt8U)PY_mb_nie},
                                    {"646","nin",(pInt8U)PY_mb_nin},
                                    {"648","niu",(pInt8U)PY_mb_niu},
                                    {"683","nue",(pInt8U)PY_mb_nve},
                                    {"686","nuo",(pInt8U)PY_mb_nuo},
                                    {"724","pai",(pInt8U)PY_mb_pai},
                                    {"726","pan",(pInt8U)PY_mb_pan},
                                    {"726","pao",(pInt8U)PY_mb_pao},
                                    {"734","pei",(pInt8U)PY_mb_pei},
                                    {"736","pen",(pInt8U)PY_mb_pen},
                                    {"743","pie",(pInt8U)PY_mb_pie},
                                    {"746","pin",(pInt8U)PY_mb_pin},
                                    {"768","pou",(pInt8U)PY_mb_pou},
                                    {"742","qia",(pInt8U)PY_mb_qia},
                                    {"743","qie",(pInt8U)PY_mb_qie},
                                    {"746","qin",(pInt8U)PY_mb_qin},
                                    {"748","qiu",(pInt8U)PY_mb_qiu},
                                    {"783","que",(pInt8U)PY_mb_que},
                                    {"786","qun",(pInt8U)PY_mb_qun},
                                    {"726","ran",(pInt8U)PY_mb_ran},
                                    {"726","rao",(pInt8U)PY_mb_rao},
                                    {"736","ren",(pInt8U)PY_mb_ren},
                                    {"768","rou",(pInt8U)PY_mb_rou},
                                    {"784","rui",(pInt8U)PY_mb_rui},
                                    {"786","run",(pInt8U)PY_mb_run},
                                    {"786","ruo",(pInt8U)PY_mb_ruo},
                                    {"724","sai",(pInt8U)PY_mb_sai},
                                    {"726","sao",(pInt8U)PY_mb_sao},
                                    {"726","san",(pInt8U)PY_mb_san},
                                    {"736","sen",(pInt8U)PY_mb_sen},
                                    {"742","sha",(pInt8U)PY_mb_sha},
                                    {"743","she",(pInt8U)PY_mb_she},
                                    {"744","shi",(pInt8U)PY_mb_shi},
                                    {"748","shu",(pInt8U)PY_mb_shu},
                                    {"768","sou",(pInt8U)PY_mb_sou},
                                    {"784","sui",(pInt8U)PY_mb_sui},
                                    {"786","sun",(pInt8U)PY_mb_sun},
                                    {"786","suo",(pInt8U)PY_mb_suo},
                                    {"824","tai",(pInt8U)PY_mb_tai},
                                    {"826","tan",(pInt8U)PY_mb_tan},
                                    {"826","tao",(pInt8U)PY_mb_tao},
                                    {"843","tie",(pInt8U)PY_mb_tie},
                                    {"868","tou",(pInt8U)PY_mb_tou},
                                    {"884","tui",(pInt8U)PY_mb_tui},
                                    {"886","tun",(pInt8U)PY_mb_tun},
                                    {"886","tuo",(pInt8U)PY_mb_tuo},
                                    {"924","wai",(pInt8U)PY_mb_wai},
                                    {"926","wan",(pInt8U)PY_mb_wan},
                                    {"934","wei",(pInt8U)PY_mb_wei},
                                    {"936","wen",(pInt8U)PY_mb_wen},
                                    {"942","xia",(pInt8U)PY_mb_xia},
                                    {"943","xie",(pInt8U)PY_mb_xie},
                                    {"946","xin",(pInt8U)PY_mb_xin},
                                    {"948","xiu",(pInt8U)PY_mb_xiu},
                                    {"983","xue",(pInt8U)PY_mb_xue},
                                    {"986","xun",(pInt8U)PY_mb_xun},
                                    {"926","yan",(pInt8U)PY_mb_yan},
                                    {"926","yao",(pInt8U)PY_mb_yao},
                                    {"946","yin",(pInt8U)PY_mb_yin},
                                    {"968","you",(pInt8U)PY_mb_you},
                                    {"983","yue",(pInt8U)PY_mb_yue},
                                    {"986","yun",(pInt8U)PY_mb_yun},
                                    {"924","zai",(pInt8U)PY_mb_zai},
                                    {"926","zan",(pInt8U)PY_mb_zan},
                                    {"926","zao",(pInt8U)PY_mb_zao},
                                    {"934","zei",(pInt8U)PY_mb_zei},
                                    {"936","zen",(pInt8U)PY_mb_zen},
                                    {"942","zha",(pInt8U)PY_mb_zha},
                                    {"943","zhe",(pInt8U)PY_mb_zhe},
                                    {"944","zhi",(pInt8U)PY_mb_zhi},
                                    {"948","zhu",(pInt8U)PY_mb_zhu},
                                    {"968","zou",(pInt8U)PY_mb_zou},
                                    {"984","zui",(pInt8U)PY_mb_zui},
                                    {"986","zun",(pInt8U)PY_mb_zun},
                                    {"986","zuo",(pInt8U)PY_mb_zuo},
                                    {"2264","bang",(pInt8U)PY_mb_bang},
                                    {"2364","beng",(pInt8U)PY_mb_beng},
                                    {"2426","bian",(pInt8U)PY_mb_bian},
                                    {"2426","biao",(pInt8U)PY_mb_biao},
                                    {"2464","bing",(pInt8U)PY_mb_bing},
                                    {"2264","cang",(pInt8U)PY_mb_cang},
                                    {"2364","ceng",(pInt8U)PY_mb_ceng},
                                    {"2424","chai",(pInt8U)PY_mb_chai},
                                    {"2426","chan",(pInt8U)PY_mb_chan},
                                    {"2426","chao",(pInt8U)PY_mb_chao},
                                    {"2436","chen",(pInt8U)PY_mb_chen},
                                    {"2468","chou",(pInt8U)PY_mb_chou},
                                    //----{"248424","chuai",(pInt8U)PY_mb_chuai},
                                    {"2484","chui",(pInt8U)PY_mb_chui},
                                    {"2484","chun",(pInt8U)PY_mb_chun},
                                    {"2486","chuo",(pInt8U)PY_mb_chuo},
                                    {"2664","cong",(pInt8U)PY_mb_cong},
                                    {"2826","cuan",(pInt8U)PY_mb_cuan},
                                    {"3264","dang",(pInt8U)PY_mb_dang},
                                    {"3364","deng",(pInt8U)PY_mb_deng},
                                    {"3426","dian",(pInt8U)PY_mb_dian},
                                    {"3426","diao",(pInt8U)PY_mb_diao},
                                    {"3464","ding",(pInt8U)PY_mb_ding},
                                    {"3664","dong",(pInt8U)PY_mb_dong},
                                    {"3826","duan",(pInt8U)PY_mb_duan},
                                    {"3264","fang",(pInt8U)PY_mb_fang},
                                    {"3364","feng",(pInt8U)PY_mb_feng},
                                    {"4264","gang",(pInt8U)PY_mb_gang},
                                    {"4364","geng",(pInt8U)PY_mb_geng},
                                    {"4664","gong",(pInt8U)PY_mb_gong},
                                    {"4824","guai",(pInt8U)PY_mb_guai},
                                    {"4826","guan",(pInt8U)PY_mb_guan},
                                    {"4264","hang",(pInt8U)PY_mb_hang},
                                    {"4364","heng",(pInt8U)PY_mb_heng},
                                    {"4664","hong",(pInt8U)PY_mb_hong},
                                    {"4823","huai",(pInt8U)PY_mb_huai},
                                    {"4826","huan",(pInt8U)PY_mb_huan},
                                    {"5426","jian",(pInt8U)PY_mb_jian},
                                    {"5426","jiao",(pInt8U)PY_mb_jiao},
                                    {"5464","jing",(pInt8U)PY_mb_jing},
                                    {"5826","juan",(pInt8U)PY_mb_juan},
                                    {"5264","kang",(pInt8U)PY_mb_kang},
                                    {"5364","keng",(pInt8U)PY_mb_keng},
                                    {"5664","kong",(pInt8U)PY_mb_kong},
                                    {"5824","kuai",(pInt8U)PY_mb_kuai},
                                    {"5826","kuan",(pInt8U)PY_mb_kuan},
                                    {"5264","lang",(pInt8U)PY_mb_lang},
                                    {"5366","leng",(pInt8U)PY_mb_leng},
                                    {"5426","lian",(pInt8U)PY_mb_lian},
                                    {"5426","liao",(pInt8U)PY_mb_liao},
                                    {"5464","ling",(pInt8U)PY_mb_ling},
                                    {"5664","long",(pInt8U)PY_mb_long},
                                    {"5826","luan",(pInt8U)PY_mb_luan},
                                    {"6264","mang",(pInt8U)PY_mb_mang},
                                    {"6364","meng",(pInt8U)PY_mb_meng},
                                    {"6426","mian",(pInt8U)PY_mb_mian},
                                    {"6426","miao",(pInt8U)PY_mb_miao},
                                    {"6464","ming",(pInt8U)PY_mb_ming},
                                    {"6264","nang",(pInt8U)PY_mb_nang},
                                    {"6364","neng",(pInt8U)PY_mb_neng},
                                    {"6426","nian",(pInt8U)PY_mb_nian},
                                    {"6426","niao",(pInt8U)PY_mb_niao},
                                    {"6464","ning",(pInt8U)PY_mb_ning},
                                    {"6664","nong",(pInt8U)PY_mb_nong},
                                    {"6826","nuan",(pInt8U)PY_mb_nuan},
                                    {"7264","pang",(pInt8U)PY_mb_pang},
                                    {"7364","peng",(pInt8U)PY_mb_peng},
                                    {"7426","pian",(pInt8U)PY_mb_pian},
                                    {"7426","piao",(pInt8U)PY_mb_piao},
                                    {"7464","ping",(pInt8U)PY_mb_ping},
                                    {"7426","qian",(pInt8U)PY_mb_qian},
                                    {"7426","qiao",(pInt8U)PY_mb_qiao},
                                    {"7464","qing",(pInt8U)PY_mb_qing},
                                    {"7826","quan",(pInt8U)PY_mb_quan},
                                    {"7264","rang",(pInt8U)PY_mb_rang},
                                    {"7364","reng",(pInt8U)PY_mb_reng},
                                    {"7664","rong",(pInt8U)PY_mb_rong},
                                    {"7826","ruan",(pInt8U)PY_mb_ruan},
                                    {"7264","sang",(pInt8U)PY_mb_sang},
                                    {"7364","seng",(pInt8U)PY_mb_seng},
                                    {"7424","shai",(pInt8U)PY_mb_shai},
                                    {"7426","shan",(pInt8U)PY_mb_shan},
                                    {"7426","shao",(pInt8U)PY_mb_shao},
                                    {"7436","shen",(pInt8U)PY_mb_shen},
                                    {"7468","shou",(pInt8U)PY_mb_shou},
                                    {"7482","shua",(pInt8U)PY_mb_shua},
                                    {"7484","shui",(pInt8U)PY_mb_shui},
                                    {"7486","shun",(pInt8U)PY_mb_shun},
                                    {"7486","shuo",(pInt8U)PY_mb_shuo},
                                    {"7664","song",(pInt8U)PY_mb_song},
                                    {"7826","suan",(pInt8U)PY_mb_suan},
                                    {"8264","tang",(pInt8U)PY_mb_tang},
                                    {"8364","teng",(pInt8U)PY_mb_teng},
                                    {"8426","tian",(pInt8U)PY_mb_tian},
                                    {"8426","tiao",(pInt8U)PY_mb_tiao},
                                    {"8464","ting",(pInt8U)PY_mb_ting},
                                    {"8664","tong",(pInt8U)PY_mb_tong},
                                    {"8826","tuan",(pInt8U)PY_mb_tuan},
                                    {"9264","wang",(pInt8U)PY_mb_wang},
                                    {"9364","weng",(pInt8U)PY_mb_weng},
                                    {"9426","xian",(pInt8U)PY_mb_xiao},
                                    {"9426","xiao",(pInt8U)PY_mb_xiao},
                                    {"9464","xing",(pInt8U)PY_mb_xing},
                                    {"9826","xuan",(pInt8U)PY_mb_xuan},
                                    {"9264","yang",(pInt8U)PY_mb_yang},
                                    {"9464","ying",(pInt8U)PY_mb_ying},
                                    {"9664","yong",(pInt8U)PY_mb_yong},
                                    {"9826","yuan",(pInt8U)PY_mb_yuan},
                                    {"9264","zang",(pInt8U)PY_mb_zang},
                                    {"9364","zeng",(pInt8U)PY_mb_zeng},
                                    {"9424","zhai",(pInt8U)PY_mb_zhai},
                                    {"9426","zhan",(pInt8U)PY_mb_zhan},
                                    {"9426","zhao",(pInt8U)PY_mb_zhao},
                                    {"9436","zhen",(pInt8U)PY_mb_zhen},
                                    {"9468","zhou",(pInt8U)PY_mb_zhou},
                                    {"9482","zhua",(pInt8U)PY_mb_zhua},
                                    {"9484","zhui",(pInt8U)PY_mb_zhui},
                                    {"9486","zhun",(pInt8U)PY_mb_zhun},
                                    {"9486","zhuo",(pInt8U)PY_mb_zhuo},
                                    {"9664","zong",(pInt8U)PY_mb_zong},
                                    {"9826","zuan",(pInt8U)PY_mb_zuan},
                                    {"24264","chang",(pInt8U)PY_mb_chang},
                                    {"24364","cheng",(pInt8U)PY_mb_cheng},
                                    {"24664","chong",(pInt8U)PY_mb_chong},
                                    {"24824","chuai",(pInt8U)PY_mb_chuai},
                                    {"24826","chuan",(pInt8U)PY_mb_chuan},
                                    {"48264","guang",(pInt8U)PY_mb_guang},
                                    {"48264","huang",(pInt8U)PY_mb_huang},
                                    {"54264","jiang",(pInt8U)PY_mb_jiang},
                                    {"54664","jiong",(pInt8U)PY_mb_jiong},
                                    {"58264","kuang",(pInt8U)PY_mb_kuang},
                                    {"54264","liang",(pInt8U)PY_mb_liang},
                                    {"64264","niang",(pInt8U)PY_mb_niang},
                                    {"74264","qiang",(pInt8U)PY_mb_qiang},
                                    {"74664","qiong",(pInt8U)PY_mb_qiong},
                                    {"74264","shang ",(pInt8U)PY_mb_shang},
                                    {"74364","sheng",(pInt8U)PY_mb_sheng},
                                    {"74824","shuai",(pInt8U)PY_mb_shuai},
                                    {"74826","shuan",(pInt8U)PY_mb_shuan},
                                    {"94264","xiang",(pInt8U)PY_mb_xiang},
                                    {"94664","xiong",(pInt8U)PY_mb_xiong},
                                    {"94264","zhang",(pInt8U)PY_mb_zhang},
                                    {"94364","zheng",(pInt8U)PY_mb_zheng},
                                    {"94664","zhong",(pInt8U)PY_mb_zhong},
                                    {"94824","zhuai",(pInt8U)PY_mb_zhuai},
                                    {"94826","zhuan",(pInt8U)PY_mb_zhuan},
                                    {"248264","chuang",(pInt8U)PY_mb_chuang},
                                    {"748264","shuang",(pInt8U)PY_mb_shuang},
                                    {"948264","zhuang",(pInt8U)PY_mb_zhuang}
								}; 

t9PINYIN_INDEX *List_match_PY_Mb[INDEX_SIZE];

//========================================================================
//	Óï·¨¸ñÊ½£º	unsigned char T9PY_Get_Match_PY_MB(unsigned char *pInputStr, Int8U len)	
//	ÊµÏÖ¹¦ÄÜ£º	»ñÈ¡ÓëÊäÈëÏàÆ¥ÅäµÄT9Æ´ÒôÁĞ±í
//	²ÎÊı£º		p_PadInput	ÊäÈëµÄ°´¼üĞòÁĞ£¬ÓÉ'0'~'9'×é³ÉµÄ×Ö·û´®
//				List_match_PY_Mb	´æ´¢"»ñÈ¡µ½µÄÆ´ÒôË÷ÒıµØÖ·"µÄÊı×é
//	·µ»ØÖµ£º	»ñÈ¡µ½ÍêÈ«Æ¥ÅäÆ´ÒôÊıÁ¿
//  ÒÆÖ²×¢Òâ£º	List_match_PY_MbËùÖ¸ÏòµÄ´æ´¢½á¹¹,¼´ÓÃÓÚ´æ·ÅÆ¥ÅäµÄÆ´ÒôÂë±íµØÖ·µÄ´æ´¢½á¹¹.
//				µÚÒ»¸öÔªËØ´æ·ÅµÄÊÇÒ»¸ö²»Æ¥ÅäµÄÆ´ÒôÂë±íµØÖ·.ÆäËûÎªÆ¥ÅäµÄÆ´ÒôÂë±íµØÖ·
//========================================================================
Int8U T9PY_Get_Match_PY_MB(unsigned char *pInputStr, Int8U len)		//
{
/******
//===========================	·½·¨Ò»	(ÒÆÖ²ÏÖÓĞµÄ)=============================
Int8U n=0;
Int16U array_sum;
t9PINYIN_INDEX	*pPY_currentIndex,*pPY_lastIndex;
Int8U index_cou=0;

//------------¼ÆËãpInputStr³¤¶È
// Int8U len=0;
// while(pInputStr[len]!='\0')
	// {
	// len++;
	// }
//----------¼ÆËãË÷Òı±ít9PinYin_Index2ÔªËØ¸öÊı£¬ÒÔµÃµ½¸÷¸öÔªËØµØÖ·
array_sum=sizeof(t9PinYin_Index2)/sizeof(t9PinYin_Index2[0]);
pPY_currentIndex=t9PinYin_Index2;
pPY_lastIndex=t9PinYin_Index2+array_sum;
//---------------
while(pPY_currentIndex<pPY_lastIndex)
	{
	while(n<len)
		{
		if(*(pInputStr+n)==*((*pPY_currentIndex).nums_str+n))
			n++;
		else
			break;
		}
	if(n==len)	//Æ¥Åä	
		{
		if(index_cou<INDEX_SIZE)	//Æ¥Åä×éÊı Î´³¬¹ıÉÏÏŞ
			{
			List_match_PY_Mb[index_cou++]=pPY_currentIndex;	//index Ö¸Õë ±£´æbuf 
			}
		}
		
	pPY_currentIndex++;		//ÏÂÒ»Ë÷Òı
	n=0;
	}
*************/
//=====================================·½·¨ ¶ş£¨¸ù¾İ·½·¨Ò»×Ô¼º×öÁË¾«¼òËã·¨£©===============
Int16U array_sum, t=0;
Int16U n=0;
pInt8U ptemp;
Int8U index_cou=0;
//----------¼ÆËãË÷Òı±ít9PinYin_Index2ÔªËØ¸öÊı£¬ÒÔµÃµ½¸÷¸öÔªËØµØÖ·
array_sum=sizeof(t9PinYin_Index2)/sizeof(t9PinYin_Index2[0]);
while(t<array_sum)
	{
	ptemp=(pInt8U)&t9PinYin_Index2[t];
	while(n<len)
		{
		if(*(pInputStr+n)==*(ptemp+n))
			n++;
		else
			break;
		}
	if(n==len)	//Æ¥Åä	
		{
		if(index_cou<INDEX_SIZE)	//Æ¥Åä×éÊı Î´³¬¹ıÉÏÏŞ
			{
			// List_match_PY_Mb[index_cou++]=(t9PINYIN_INDEX *)ptemp;	//±£´æbuf
			List_match_PY_Mb[index_cou++]=&t9PinYin_Index2[t];	//±£´æbuf£¨Í¬ÉÏ£©
			}
		}
	n=0;	
	t++;
	}

//-----------------
return 	index_cou;//Æ¥Åä×éÊı
}

