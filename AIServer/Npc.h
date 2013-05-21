#pragma once

#include "NpcTable.h"
#include "NpcMagicProcess.h"

#define MAX_PATH_SIZE		100

#define NPC_MAX_USER_LIST	5

#define NPC_ATTACK_SHOUT	0
#define NPC_SUBTYPE_LONG_MON 1

#define NPC_TRACING_STEP	100

#define NPC_HAVE_USER_LIST	5
#define NPC_HAVE_ITEM_LIST	6
#define NPC_PATTEN_LIST		5
#define NPC_PATH_LIST		50
#define NPC_MAX_PATH_LIST	100
#define NPC_EXP_RANGE		50
#define NPC_EXP_PERSENT		50

#define NPC_SECFORMETER_MOVE	4
#define NPC_SECFORMETER_RUN		4
#define NPC_VIEW_RANGE			100

#define MAX_MAGIC_TYPE3			20
#define MAX_MAGIC_TYPE4			9

struct  _NpcSkillList
{
	short	sSid;
	uint8	tLevel;
	uint8	tOnOff;
};

struct  _NpcGiveItem
{
	int 	sSid;			// item serial number
	short	count;			// item ����(���� ����)
};

struct	_ExpUserList
{
	char	strUserID[MAX_ID_SIZE+1];		// ���̵�(ĳ���� �̸�)
	int		iUid;							// User uid
	int		nDamage;						// Ÿ��ġ ��
	BOOL	bIs;							// �þ߿� �����ϴ����� �Ǵ�(true:����)
	//BOOL	bSameParty;						// ���� ��Ƽ �Ҽ��� �ִٸ� TRUE, �׷��� ������ FALSE
};

struct _Target
{
	int	id;							// ���ݴ�� User uid
	float x;						// User�� x pos
	float y;						// User�� y pos
	float z;						// User�� z pos
	int failCount;
};

struct _PattenPos
{
	short x;
	short z;
};

struct _Patten
{
	int	patten_index;
	_PattenPos pPattenPos[NPC_MAX_PATH_LIST];
};

struct _PathList
{
	_PattenPos pPattenPos[NPC_MAX_PATH_LIST];
};

struct _MagicType3
{
	short		sHPAttackUserID;	// ���� ������ ����� ������ ���̵� ����
	short		sHPAmount;			// ���� damage ( �����Ѿ� / (���ӽð� / 2) )
	uint8		byHPDuration;		// ���� �ð�
	uint8		byHPInterval;		// ���� ����
	time_t		tStartTime;	
};

struct _MagicType4
{
	uint8	byAmount;
	short	sDurationTime;		// duration, in seconds
	time_t	tStartTime;
};

struct _TargetHealer
{
	short	sNID;				// npc nid
	short	sValue;				// ����
};

class MAP;

struct __Vector3;
class CNpc  
{
public:
	CNpcTable *m_proto;

	_Target	m_Target;				// ������ ���� ����,,
	short		m_ItemUserLevel;		// ������ ���� �̻� �����۸� ���������� �����ؾ��ϴ� �����Ƿ���

	int		m_TotalDamage;	// �� ������ �������
	_ExpUserList m_DamagedUserList[NPC_HAVE_USER_LIST]; // ������ Ÿ��ġ�� �� ���������� ����Ʈ�� �����Ѵ�.(����ġ �й�)
	short   m_sMaxDamageUserid;		// ������ �ְ��� �������� �� ������ ���̵� ����..

	_PathList m_PathList;			// Npc�� �н� ����Ʈ 
	_PattenPos m_pPattenPos;		// Npc�� ����,,

	//int m_iPattenNumber;		// ������ ���Ϲ�ȣ
	short m_iPattenFrame;			// ������ ���� ��ġ..

	uint8 m_byMoveType;			// NPC�� �ൿŸ��(�̵�����)
	uint8 m_byInitMoveType;		// NPC�� �ʱ� �ൿŸ��(�̵�����)
	short m_sPathCount;			// NPC�� PathList Count
	short m_sMaxPathCount;		// NPC�� PathList Max Count

	BOOL	m_bFirstLive;		// NPC �� ó�� �����Ǵ��� �׾��� ��Ƴ����� �Ǵ�.
	uint8	m_NpcState;			// NPC�� ���� - ��Ҵ�, �׾���, ���ִ� ���...
	MAP *	m_pZone;

	short	m_sNid;				// NPC (��������)�Ϸù�ȣ

	float		m_nInitX;			// ó�� ������ ��ġ X
	float		m_nInitY;			// ó�� ������ ��ġ Y
	float		m_nInitZ;			// ó�� ������ ��ġ Z

	uint8		m_bCurZone;			// Current Zone;
	float		m_fCurX;			// Current X Pos;
	float		m_fCurY;			// Current Y Pos;
	float		m_fCurZ;			// Current Z Pos;

	float		m_fPrevX;			// Prev X Pos;
	float		m_fPrevY;			// Prev Y Pos;
	float		m_fPrevZ;			// Prev Z Pos;

	//
	//	PathFind Info
	//
	short		m_min_x;
	short		m_min_y;
	short		m_max_x;
	short		m_max_y;

	SIZE	m_vMapSize;

	float m_fStartPoint_X, m_fStartPoint_Y;
	float m_fEndPoint_X, m_fEndPoint_Y;

	short m_sStepCount;

	CPathFind m_vPathFind;
	_PathNode	*m_pPath;

	int		m_nInitMinX;					// �ʱ���ġ
	int		m_nInitMinY;
	int		m_nInitMaxX;
	int		m_nInitMaxY;

	// ���� ���� ����..
	time_t	m_fHPChangeTime;			// Hp ȸ����
	time_t	m_tFaintingTime;			// ������ �ִ� �ð�..
	_MagicType3  m_MagicType3[MAX_MAGIC_TYPE3];			// HP ���õ� ����..
	_MagicType4  m_MagicType4[MAX_MAGIC_TYPE4];			// �ɷ�ġ ���õ� ����..

	//----------------------------------------------------------------
	//	MONSTER DB �ʿ� �ִ� ������
	//----------------------------------------------------------------
	short   m_sSize;						// ĳ������ ����(100 �ۼ�Ʈ ����)
	int     m_iWeapon_1;			// ���� ����
	int     m_iWeapon_2;			// ���� ����
	uint8	m_byGroup;			// �Ҽ�����(���� ����)
	uint8	m_byActType;		// �ൿ����
	uint8	m_byRank;			// ����
	uint8	m_byTitle;			// ����
	int 	m_iSellingGroup;	// ������ �׷�(���ǸŸ� ��� NPC�� ��츸)
	int		m_iMaxHP;			// �ִ� HP
	short	m_sMaxMP;			// �ִ� MP
	short	m_sAttack;			// ���ݰ�(���� ������� ����..)
	short	m_sDefense;			// ��
	short	m_sHitRate;			// ���ݹ�ø
	short   m_sEvadeRate;		// ����ø
	short	m_sDamage;			// �⺻ ������ - ���ݰ�
	short	m_sAttackDelay;		// ���ݵ�����
	short	m_sSpeed;			// �̵��ӵ�	
	float   m_fSpeed_1;			// �⺻ �̵� Ÿ��		(1�ʿ� �� �� �ִ� �Ÿ�)
	float   m_fSpeed_2;			// �ٴ� �̵� Ÿ��..		(1�ʿ� �� �� �ִ� �Ÿ�)
	short	m_sStandTime;		// ���ִ� �ð�
	uint16	m_byFireR;			// ȭ�� ���׷�
	uint16	m_byColdR;			// �ñ� ���׷�
	uint16	m_byLightningR;		// ���� ���׷�
	uint16	m_byMagicR;			// ���� ���׷�
	uint16	m_byDiseaseR;		// ���� ���׷�
	uint16	m_byPoisonR;		// �� ���׷�
	uint8	m_bySearchRange;	// �� Ž�� ����
	uint8	m_byAttackRange;	// �����Ÿ�
	uint8	m_byTracingRange;	// �߰� �Ÿ�

	uint8	m_tItemPer;			// �������� ������ Ȯ��
	uint8	m_tDnPer;			// ���� ������Ȯ��
	uint8	m_byMoneyType;		// Event������ ��� ���� ���� �ִ� ��, (0:����, 1:������ ���� �ʰ� �ٷ� �������´�)

	int		m_iMoney;			// �������� ��
	int		m_iItem;			// �������� ������
	//BYTE	m_byMemory;			// ���� Ÿ�� 

	int			m_iHP;				// ���� HP
	short		m_sMP;				// ���� MP
	
	float   m_fSecForMetor;		// �ʴ� �� �� �ִ� �Ÿ�..

	//----------------------------------------------------------------
	//	MONSTER AI�� ���õ� ������
	//----------------------------------------------------------------
	uint8	m_tNpcLongType;		// ���� �Ÿ� : ���Ÿ�(1), �ٰŸ�(0), ��.����(2)
	uint8	m_tNpcAttType;		// ���� ���� : ����(1), �İ�(0)
	uint8	m_tNpcOldAttType;	// ���� ���� : ����(1), �İ�(0) (Ȱ������ ����)
	uint8	m_tNpcGroupType;	// ������ �����ϳ�(1), ���ϳ�?(0)
	uint8	m_byNpcEndAttType;	// ���������� �ο��(1), �׷��� ������(0)
//	uint8	m_tNpcTraceType;	// ������ ���󰣴�(1), �þ߿��� �������� �׸�(0)
	uint8	m_byAttackPos;		// User�� ��� �κп��� �����ϴ����� �Ǵ�(8����)
	uint8	m_byBattlePos;		// � ������ ������ �������� �Ǵ�..
	uint8	m_byWhatAttackType; // ���� Ÿ�� : Normal(0), ��.��Ÿ�����(1), ��(2), ����(3), ����������(4), 1+4�� ����(5)
	uint8	m_byGateOpen;		// ������ ��쿡.. ���... Gate Npc Status -> 1 : open 0 : close
	uint8	m_byMaxDamagedNation;	// ���� ���� ������ ������ ����.. (1:ī�罺, 2:������)
	uint8	m_byObjectType;         // ������ 0, objectŸ��(����, ����)�� 1
	uint8	m_byDungeonFamily;		// �������� ���� �йи� ���� (���� ��)
	uint8	m_bySpecialType;		// ������ ���°� ���ϴ����� �Ǵ�(0:������ ����, 1:���ϴ� ����, 
									// 2:�״°�� �����ϴ� ����(������� ������� ������ ����), 
									// 3:��������� ������ ������ �ִ� ����(������Ͱ� ������ ����Ǵ� ���ʹ� ���� �׵���)
									// 4:���ϸ鼭 �״°�� �����ϴ� ���� (m_sControlSid)
									// 5:ó���� �׾��ִٰ� �����ϴ� ����,,
									// 6:�����ð��� ���� �Ŀ� �ൿ�ϴ� ����,,
									// 100:�׾����� �������� ���� ���� ������ ����� �ּ���
	uint8	m_byTrapNumber;			// �������� Ʈ���� ��ȣ,,
	uint8	m_byChangeType;			// 0:�������, 1:���ϱ� ���� �غ�, 2:�ٸ����ͷ� ����, 3:������ ����, 100:������ ����
	uint8	m_byRegenType;			// 0:���������� ������ ��.. , 1:�ѹ� ������ ������ �ȵǴ� Ư�� ��, 2:������ �ȵ�
	uint8    m_byDeadType;			// 0:��� �ִ� ���, 100:�����̺�Ʈ�� ���� ���
	short   m_sChangeSid;			// ���ϴ� ������ Sid��ȣ..
	short   m_sControlSid;			// �����ϴ� ������ Sid��ȣ..


	//----------------------------------------------------------------
	//	MONSTER_POS DB �ʿ� �ִ� ������
	//----------------------------------------------------------------
	time_t	m_Delay;			// this doesn't really need to be time_t, but we'll use it (at least for now) for consistency
	time_t	m_fDelayTime;		// Npc Threadüũ Ÿ��...

	uint8	m_byType;
	int		m_sRegenTime;		// NPC ����ð�
	
	uint8	m_byDirection;

	int		m_nLimitMinX;		// Ȱ�� ����
	int		m_nLimitMinZ;
	int		m_nLimitMaxX;
	int		m_nLimitMaxZ;

	long	m_lEventNpc;

	float m_fAdd_x;
	float m_fAdd_z;

	float m_fBattlePos_x;	
	float m_fBattlePos_z;

	float m_fSecForRealMoveMetor;		// �ʴ� �� �� �ִ� �Ÿ�..(���� Ŭ���̾�Ʈ�� �����ִ� �Ÿ�)

	BOOL m_bPathFlag;					// �н� ���ε� ���࿩�� üũ ����..

	//----------------------------------------------------------------
	//	NPC �̵� ����
	//----------------------------------------------------------------
	_NpcPosition	m_pPoint[MAX_PATH_LINE];			// �̵��� ���� ��ǥ

	short m_iAniFrameIndex;
	short m_iAniFrameCount;
	uint8 m_byPathCount;					// �н��� ���� �̵��ϴ� ���� ���� ��ġ�� �ʵ���,, 
	uint8 m_byResetFlag;					// �������ݽ� �н����ε��� �ٽ� �Ұ�����,, ���������� �Ǵ�..
	uint8 m_byActionFlag;				// �ൿ��ȭ �÷��� ( 0 : �ൿ��ȭ ����, 1 : ���ݿ��� �߰�)

	bool m_bTracing;
	float m_fTracingStartX, m_fTracingStartZ;

	short m_iRegion_X;					// ������ region - x pos
	short m_iRegion_Z;					// ������ region - z pos
	short m_iFind_X[4];					// find enemy���� ã�� Region�˻翵��
	short m_iFind_Y[4];

	float   m_fOldSpeed_1;			// �⺻ �̵� Ÿ��		(1�ʿ� �� �� �ִ� �Ÿ�)
	float   m_fOldSpeed_2;			// �ٴ� �̵� Ÿ��..		(1�ʿ� �� �� �ִ� �Ÿ�)

public:
	INLINE MAP * GetMap() { return m_pZone; };

	CNpc();
	virtual ~CNpc();

	void Init();	//	NPC �⺻���� �ʱ�ȭ
	void InitTarget(void);
	void InitUserList();
	void InitPos();
	void InitMagicValuable();

	void Load(uint16 sNpcID, CNpcTable * proto);

protected:
	void ClearPathFindData(void);

public:

	void FillNpcInfo(Packet & result);
	void NpcStrategy(BYTE type);
	void NpcTypeParser();
	int  FindFriend(int type=0);
	void  FindFriendRegion(int x, int z, MAP* pMap, _TargetHealer* pHealer, int type=0);
	//void  FindFriendRegion(int x, int z, MAP* pMap, int type=0);
	BOOL IsCloseTarget(CUser *pUser, int nRange);
	void ToTargetMove(CUser* pUser);
	int SendDead(int type = 1);			// Npc Dead
	void SendExpToUserList();								// User ����ġ �й�..
	BOOL SetDamage(int nAttackType, int nDamage, TCHAR *id, int uid);	// Npc�� ������ ���..
	BOOL SetHMagicDamage(int nDamage);	// Npc�� ������ ���..
	int GetDefense();										// Npc�� ��..
	void ChangeTarget(int nAttackType, CUser *pUser);
	void ChangeNTarget(CNpc *pNpc);
	int GetFinalDamage(CUser *pUser, int type = 1);
	int GetNFinalDamage(CNpc *pNpc);
	BYTE GetHitRate(float rate);
	BOOL ResetPath();
	BOOL GetTargetPos(float& x, float& z);
	BOOL IsChangePath();
	int Attack();
	int LongAndMagicAttack();
	int TracingAttack();
	int GetTargetPath(int option = 0);
	int	GetPartyDamage(int iNumber);
	int IsCloseTarget(int nRange, int Flag=0);
	BOOL StepMove();
	BOOL StepNoPathMove();
	BOOL IsMovingEnd();
	BOOL IsMovable(float x, float z);
	int  IsSurround(CUser* pUser);
	BOOL IsDamagedUserList(CUser *pUser);
	void IsUserInSight();
	BOOL IsLevelCheck(int iLevel);
	BOOL IsHPCheck(int iHP);
	BOOL IsCompStatus(CUser* pUser);
	BOOL IsPathFindCheck(float fDistance);						// �н� ���ε带 �Ұ������� üũ�ϴ� ��ƾ..
	void IsNoPathFind(float fDistance);						// �н� ���ε带 ���� �ʰ� ���ݴ������ ���� ��ƾ..
	BOOL IsInExpRange(CUser* pUser);
	void GiveNpcHaveItem();		// NPC �� ���� �������� ������

	time_t NpcLive();
	time_t NpcFighting();
	time_t NpcTracing();
	time_t NpcAttacking();
	time_t NpcMoving();
	time_t NpcSleeping();
	time_t NpcFainting();
	time_t NpcHealing();
	time_t NpcStanding();
	time_t NpcBack();
	BOOL SetLive();

	BOOL IsInRange(int nX, int nZ);
	BOOL RandomMove();				//
	BOOL RandomBackMove();				//
	BOOL IsInPathRange();			//
	int GetNearPathPoint();			//

	// Packet Send�κ�..
	void SendAttackSuccess(BYTE byResult, int tuid, short sDamage, int nHP=0, BYTE byFlag = 0, short sAttack_type=1);

	// Inline Function
	BOOL SetUid(float x, float z, int id);

	void Dead(int iDeadType = 0);
	BOOL FindEnemy();
	BOOL CheckFindEnermy();
	int FindEnemyRegion();
	float FindEnemyExpand(int nRX, int nRZ, float fCompDis, int nType);
	int GetMyField();

	int GetDir(float x1, float z1, float x2, float z2);
	void NpcMoveEnd();

	inline float RandomGenf(float max, float min);
	void GetVectorPosition(__Vector3 & vOrig, __Vector3 & vDest, float fDis, __Vector3 * vResult);
	void CalcAdaptivePosition(__Vector3 & vPosOrig, __Vector3 & vPosDest, float fAttackDistance, __Vector3 * vResult);
	void ComputeDestPos(__Vector3 & vCur, float fDegree, float fDegreeOffset, float fDistance, __Vector3 * vResult);
	void Yaw2D(float fDirX, float fDirZ, float& fYawResult);
	float GetDistance(__Vector3 & vOrig, __Vector3 & vDest);
	int  PathFind(CPoint start, CPoint end, float fDistance);
	BOOL GetUserInView();	// Npc�� ���� �Ÿ��ȿ� User�� �ִ����� �Ǵ�
	BOOL GetUserInViewRange(int x, int z);
	void MoveAttack();
	void HpChange();
	void MSpChange(int type, int amount);
	void ItemWoreOut( int type, int damage );
	int	 ItemProdution(int item_number);
	int  GetItemGrade(int item_grade);
	int  GetItemCodeNumber(int level, int item_type);
	int  GetWeaponItemCodeNumber(int item_type);
	void DurationMagic_4();
	void DurationMagic_3();
	void ChangeMonsterInfomation(int iChangeType);
	int  GetPartyExp( int party_level, int man, int nNpcExp );
	void ChangeAbility(int iChangeType);
	BOOL Teleport();
};