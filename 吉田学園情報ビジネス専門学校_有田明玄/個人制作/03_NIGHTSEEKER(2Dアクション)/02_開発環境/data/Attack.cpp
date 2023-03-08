//=================================================
// Content     (�G�t�F�N�g�̏���)(Attack.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/11/04)
//=================================================
#include"Attack.h"
#include"player.h"
#include"sound.h"

//�}�N����`
#define NUM_ATTACK		(5)			//�e�N�X�`���̖���
#define WEAPON_SIZE		(40.0f)		//����̑傫��
#define EFFECT_SPEED	(1)			//�G�t�F�N�g�̑��x

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureAttack = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttack = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWeapon = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWeapon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Attack g_Attack;									//�G�t�F�N�g�̏��
static Weapon s_weapon;								//����̏��
//============================
//�G�t�F�N�g�̏���������
//============================
void InitAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Attack000.png",
		&g_pTextureAttack);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAttack,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);

	//����̏��̏�����
		//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_Attack.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	g_Attack.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	g_Attack.fRadiuswidth = 0;							//���a(�傫��)
	g_Attack.bUse = false;								//�g�p���Ă��邩�ǂ����̔���
	g_Attack.nCntAnim = 0;								//�G�t�F�N�g�̃J�E���^�[
	g_Attack.nPtnAnim = 0;								//�A�j���[�V�����̔ԍ�

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffAttack->Unlock();

//����̐ݒ�
		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\weapon000.png",
		&g_pTextureWeapon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWeapon,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
	//�Ίp���̒������Z�o����
	s_weapon.fLength = sqrtf((WEAPON_SIZE*WEAPON_SIZE) + (WEAPON_SIZE*WEAPON_SIZE)) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	s_weapon.fAngle = atan2f(WEAPON_SIZE, WEAPON_SIZE);
	//����̏��̏�����
	//���_���W�̐ݒ�
	pVtx[0].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	s_weapon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	s_weapon.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	g_Attack.fRadiuswidth = 0;							//���a(�傫��)
	s_weapon.bDisp = false;								//�g�p���Ă��邩�ǂ����̔���

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWeapon->Unlock();
}
//===========================
//�G�t�F�N�g�̏I������
//===========================
void UninitAttack(void)
{
	if (g_pTextureAttack != NULL)
	{
		g_pTextureAttack->Release();
		g_pTextureAttack = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffAttack != NULL)
	{
		g_pVtxBuffAttack->Release();
		g_pVtxBuffAttack = NULL;
	}
	if (g_pTextureWeapon != NULL)
	{
		g_pTextureWeapon->Release();
		g_pTextureWeapon = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffWeapon != NULL)
	{
		g_pVtxBuffWeapon->Release();
		g_pVtxBuffWeapon = NULL;
	}
}
//===========================
//�G�t�F�N�g�̍X�V����
//===========================
void UpdateAttack(void)
{

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);
	if (g_Attack.bUse == true)
	{//�G�t�F�N�g���g�p����Ă���
		if (g_Attack.nCntAnim++ % EFFECT_SPEED == 0)
		{
			if (g_Attack.nPtnAnim++ >= NUM_ATTACK - 1)
			{
				g_Attack.nPtnAnim = 0;
				g_Attack.bUse = false;
			}
		}
		Player*pPlayer = GetPlayer();
		g_Attack.pos += pPlayer->move;//����̒��S�_�Ƀv���C���[�̈ړ��ʂ����Z
		g_Attack.pos.y -= 1.0f;
		//��ʂ̒����ɗ������̐ݒ�
		CenterPlayer(&g_Attack.pos);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight/2, 0.0f) + g_Attack.pos;
		pVtx[1].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight/2, 0.0f) + g_Attack.pos;
		pVtx[2].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[3].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*((g_Attack.nPtnAnim + 1) * g_Attack.nDirection), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*g_Attack.nPtnAnim*g_Attack.nDirection, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*((g_Attack.nPtnAnim + 1)* g_Attack.nDirection), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*g_Attack.nPtnAnim*g_Attack.nDirection, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffAttack->Unlock();

	//���̍X�V
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
	if (s_weapon.bDisp == true)
	{//���킪�g�p����Ă���
		Player*pPlayer = GetPlayer();
		s_weapon.pos += pPlayer->move;//����̒��S�_�Ƀv���C���[�̈ړ��ʂ����Z
		s_weapon.pos.y -= 1.0f;
		//��ʂ̒����ɗ������̐ݒ�
		CenterPlayer(&s_weapon.pos);
		//���������炷
		if (s_weapon.nLife--<=0)
		{
			s_weapon.bDisp = false;
		}
		//���_���W�̍X�V
		pVtx[0].pos.x = s_weapon.pos.x  + sinf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = s_weapon.pos.x  + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = s_weapon.pos.x   + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = s_weapon.pos.x   + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.z = 0.0f;

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffWeapon->Unlock();
	}
}
//===========================
//�G�t�F�N�g�̕`�揈��
//===========================
void DrawAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAttack, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureAttack);

		if (g_Attack.bUse == true)
		{
			//�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				0,										//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWeapon, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWeapon);

		if (s_weapon.bDisp == true)
		{
			//�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				0,										//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}
}
//===========================
//�G�t�F�N�g�̐ݒ菈��
//===========================
void SetAttack(float posx, float posy, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight,int nDirection)
{
	if (g_Attack.bUse == false)
	{
		VERTEX_2D*pVtx;
		//���̐ݒ�
		g_Attack.pos.x = posx;
		g_Attack.pos.y = posy;
		g_Attack.pos.z = 0.0f;
		g_Attack.col = col;
		g_Attack.fRadiuswidth = fRadiuswidth;
		g_Attack.fRadiusheight = fRadiusheight;
		g_Attack.nCntAnim = 0;
		g_Attack.nPtnAnim = 0;
		g_Attack.bUse = true;
		g_Attack.nDirection = nDirection;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�	(�傫��������������)
		pVtx[0].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[1].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[2].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[3].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_Attack.col;
		pVtx[1].col = g_Attack.col;
		pVtx[2].col = g_Attack.col;
		pVtx[3].col = g_Attack.col;

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffAttack->Unlock();
	}
}
//===========================
//����̐ݒ�
//===========================
void Setweapon(float posx, float posy,float posz, D3DXCOLOR col, int Life,bool collision)
{
	VERTEX_2D*pVtx;
	if (s_weapon.bDisp == false)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
		//�Ίp���̒������Z�o����
		s_weapon.fLength = sqrtf((WEAPON_SIZE*WEAPON_SIZE) + (WEAPON_SIZE*WEAPON_SIZE)) / 1.0f;

		//�Ίp���̊p�x���Z�o����
		s_weapon.fAngle = atan2f(WEAPON_SIZE, WEAPON_SIZE);
				
		s_weapon.pos.x = posx;				//�ʒu
		s_weapon.pos.y = posy;				//�ʒu
		s_weapon.pos.z = posz;
		s_weapon.col = col;					//�F
		s_weapon.nLife=Life;				//����
		s_weapon.bDisp=true;				//�g�p���Ă��邩�ǂ����̔���
		s_weapon.bCollision= collision;		//�����蔻����g�����ǂ���

		//����̏��̏�����
		//���_���W�̐ݒ�
		pVtx[0].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�ݒ�
		pVtx[0].col = s_weapon.col;
		pVtx[1].col = s_weapon.col;
		pVtx[2].col = s_weapon.col;
		pVtx[3].col = s_weapon.col;

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffWeapon->Unlock();
	}
}
//===========================
//����̓����蔻��ݒ�
//===========================
bool CollisionWeapon(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height)
{
	bool bIsHit = false;		//���n���Ă��邩�ǂ���

	//����ɑ��肪�Ԃ�������
	if (s_weapon.bDisp == true && s_weapon.bCollision == true)
	{//���킪�g�p����Ă��� 
		 //�G�Ƀv���C���[�̍U�����Ԃ�������
		if (pPos->y >= s_weapon.pos.y - WEAPON_SIZE
			&& pPos->y - Height <= s_weapon.pos.y
			&&pPos->x - Width / 2 <= s_weapon.pos.x + WEAPON_SIZE
			&& pPos->x + Width / 2 >= s_weapon.pos.x - WEAPON_SIZE)
		{//�v���C��-�ƃv���C���[������������
			bIsHit = true;
			PlaySound(SOUND_LABEL_SE_HITSWORDATTACK);
			pMove->y = 0;
		}
	}
	return bIsHit;
}