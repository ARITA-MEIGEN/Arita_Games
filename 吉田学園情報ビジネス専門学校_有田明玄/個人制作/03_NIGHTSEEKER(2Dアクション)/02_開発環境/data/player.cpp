//=================================================
// Content     (�v���C���[�̑���)(player.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/10/04)
//=================================================
#include"player.h"
#include"input.h"
#include"playereffect.h"
#include"block.h"
#include"Attack.h"
#include"game.h"
#include"enemy.h"
#include"effect.h"
#include"boss.h"
#include"bullet.h"
#include"boss.h"
#include"sound.h"

//�X�^�e�B�b�N�ϐ�
static LPDIRECT3DTEXTURE9 s_pTexturePlayer = NULL;				//�v���C���[�̃e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPlayer = NULL;			//�v���C���[�̒��_�o�b�t�@�ւ̃|�C���^
static Player s_Player;											//�v���C���[�̏��
static int s_nTimer;											//���v
static int s_Commandmemory[MAX_KEYMEMORY];						//�R�}���h�Z�p�������[

//�v���g�^�C�v�錾
static void ResetPlayer(void);						//������
static void ControlPlayer(void);					//����֌W�̏���
static void GroundPlayer(void);						//�n�ʂɖʂ��Ă��鎞�̏���
static void ComandPlayer(void);						//�R�}���h�Z
static void	KeyMemory(int nKey);					//���͏��̋L��
static void SidePlayer(void);						//��ʊO�ɂ������̏���
static void UpdatePlayerState(void);				//���X�V
static void PlayerJunp(void);						//�W�����v�֌W�̏���
static void PlayerPositionUpdate(void);				//�ʒu�̍X�V
static void Playerstate(void);						//��ԊǗ�
static void PlayerAttack(void);						//�v���C���[�̍U��
//======================================================
//�v���C���[�̏���������
//======================================================
void InitPlayer(void)
{
    ResetPlayer();		//�v���C���[�̏��̏�����
}
//======================================================
//�v���C���[�̏I������
//======================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (s_pTexturePlayer != NULL)
	{
		s_pTexturePlayer->Release();
		s_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@��j��
	if (s_pVtxBuffPlayer != NULL)
	{
		s_pVtxBuffPlayer->Release();
		s_pVtxBuffPlayer = NULL;
	}
}
//======================================================
//�v���C���[�̍X�V����
//======================================================
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;
	if (s_Player.bDisp==true)
	{
		s_Player.bIsDashing = false;	//�_�b�V������

		//�v���C���[�̑���֌W
		ControlPlayer();

		//�v���C���[�̈ʒu�̍X�V�֌W�̏���
		PlayerPositionUpdate();

		//�v���C���[�̃R�}���h�Z
		ComandPlayer();

		//�u���b�N�̓����蔻��ƒ��n����
		s_Player.bIsJumping = !CollisionBlock(&s_Player.pos, &s_Player.posOld, &s_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT, &s_Player.pBlock);

		//�G�l�~�[�̓����蔻��
		CollisionEnemy(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//�e�̓����蔻��
		CollisionBullet(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//�{�X�̓����蔻��
		CollisionBoss(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//�v���C���[����ʊO�ɓ��B�����ۂɃ��[�v�����鏈��
		SidePlayer();

		//�ړ��ʍX�V(����������)
		s_Player.move.x += (0.0f - s_Player.move.x)*MIN_SPEED;
		s_Player.move.y += 1.0f;

		//�n�ʂɐڂ��Ă��鎞�̏���
		GroundPlayer();

		//�v���C���[�̃W�����v�֌W�̏���
		PlayerJunp();

		//�_�b�V�����̎c���̐ݒ�
		if (s_nTimer % 5 == 0 && s_Player.bIsDashing == true)
		{//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�c���̐ݒ�
			SetPlayereffect(s_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.5f), (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 60, pVtx[0].tex, pVtx[1].tex, pVtx[2].tex, pVtx[3].tex);

			//���_�o�b�t�@���A�����b�N
			s_pVtxBuffPlayer->Unlock();
		}

		//�v���C���[�̏��X�V
		UpdatePlayerState();

		//�v���C���[�̍U��
		PlayerAttack();

		//��ɑ̗͂�����悤�ɂ���
		s_Player.nLife--;
	}
		//�v���C���[�̏�ԊǗ�
		Playerstate();

	if (s_Player.nLife <= 0)
	{
		HitPlayer(0);
	}
	s_nTimer++;		//�^�C�}�[�J�E���g����
}
//======================================================
//�v���C���[�̕`�揈��
//======================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�v���C���[���g�p����Ă�����
	if (s_Player.bDisp == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_pTexturePlayer);

		//�v���C���[�̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//======================================================
//�v���C���[�̐ݒ�
//======================================================
void SetPlayer(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (s_Player.bDisp == false)
	{//�u���b�N���g�p����Ă��Ȃ�
		s_Player.pos = pos;
		s_Player.nLife = MAX_PLIFE;
		s_Player.state = PLAYERSTATE_NORMAL;		//�ʏ��Ԃɂ���
		s_Player.bDisp = true;						//�g�p���Ă����Ԃɂ���

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
		pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
		pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;
		pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove + TEX_X, 0.0f);	//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove) - TEX_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove + TEX_X, 0.2f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove) - TEX_X, 0.2f);
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//�v���C���[�̑���֌W�̏���
//======================================================
void ControlPlayer(void)
{
	//���_���W�ւ̃|�C���^
	if (GetKeyboardPress(DIK_LSHIFT) == true|| GetJoypadPress(JOYKEY_RB) == true)
	{//LSHIFT�Ń_�b�V����Ԃֈȍ~
		s_Player.bIsDashing = true;
	}
	if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true || GetJoypadStick(JOYKEY_LSTICK).x <= -1.0f)
	{//A�L�[�������ꂽ
		s_Player.nDirectionMove = 1;		//�������ɂ���
		if (s_Player.bIsDashing == true)
		{
			s_Player.move.x -= sinf(D3DX_PI*0.5f)*DASH_SPEED;
		}
		else
		{
			s_Player.move.x -= sinf(D3DX_PI*0.5f)*NOMAL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true || GetJoypadStick(JOYKEY_LSTICK).x >= 1.0f)
	{//D�L�[�������ꂽ
		s_Player.nDirectionMove =0;			//�E�����ɂ���
		if (s_Player.bIsDashing == true)
		{
			s_Player.move.x += sinf(D3DX_PI*0.5f)*DASH_SPEED;
		}
		else
		{
			s_Player.move.x += sinf(D3DX_PI*0.5f)*NOMAL_SPEED;
		}
	}
	//�U���̐ݒ�
	if (GetKeyboardTrigger(DIK_RETURN) == true && s_Player.bAtk != true || GetJoypadPress(JOYKEY_X) == true && s_Player.bAtk != true)
	{//ENTER�L�[�������ꂽ
		int Direction = (s_Player.nDirectionMove == 1) ? -1 : 1;
		s_Player.bAtk = true;
		s_Player.nCntCounterAnim = 0;			//�A�j���J�E���^�[�̃��Z�b�g
		s_Player.nCntPtnAnim = 0;				//�p�^�[���̃��Z�b�g
		s_Player.nCntAtk = ALL_ATKTIME1;		//��ԊǗ��J�E���^�[�̐ݒ�
		Setweapon(s_Player.pos.x - 40.0f*Direction, s_Player.pos.y - 14.0f, 2.0f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), FIRST_ATKTIME,false);
		PlaySound(SOUND_LABEL_SE_SWORDATTACK);
	}
}
//======================================================
//�v���C���[���n�ʂɖʂ��Ă��鎞�̏���
//======================================================
void GroundPlayer(void)
{
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (s_Player.bIsJumping == false && s_Player.bAtk == false)
	{//�W�����v���Ă��Ȃ��Ƃ�
		if(s_Player.move.x < MIN_SPEED && s_Player.move.x > -MIN_SPEED)
		{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove+ TEX_X, 0.01f);	//�E���ɍ��W���w��
				pVtx[1].tex = D3DXVECTOR2(0.25f*(1+s_Player.nDirectionMove)- TEX_X, 0.01f);
				pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove+ TEX_X, 0.2f);
				pVtx[3].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove)- TEX_X, 0.2f);
		}
		else if (s_Player.move.x >= MIN_SPEED || s_Player.move.x <= -MIN_SPEED)
		{//�ړ����̏ꍇ�A�j���[�V�������X�V
			if (s_Player.nCntCounterAnim++ % 10 == 0)
			{
				s_Player.nCntPtnAnim++;
				s_Player.nCntPtnAnim %= 4;
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));	//�E���ɍ��W���w��
			pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));
			pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
		}
	}
			
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//�v���C���[�̃R�}���h�Z
//======================================================
void ComandPlayer(void)
{
	//�L�[�̋L������
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		KeyMemory(DIK_W);
	}
	else if (GetKeyboardTrigger(DIK_A) == true)
	{
		KeyMemory(DIK_A);
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{
		KeyMemory(DIK_S);
	}
	else if (GetKeyboardTrigger(DIK_D) == true)
	{
		KeyMemory(DIK_D);
	}
	//�n�C�W�����v
	if (s_Commandmemory[0] == DIK_S&& s_Commandmemory[1] == DIK_S&& GetKeyboardTrigger(DIK_RETURN)==true)
	{
		s_Player.move.y -= 30.0f;
	}
	//�����ړ�
	if (s_Commandmemory[0] == DIK_A&& s_Commandmemory[1] == DIK_S&& s_Commandmemory[2] == DIK_D&& GetKeyboardTrigger(DIK_RETURN) == true)
	{
		s_Player.bIsDashing = true;
		s_Player.move.x -= 30.0f;
	}
}
//======================================================
//�v���C���[�̓��͏��̋L��
//======================================================
void KeyMemory(int nKey)		
{
	int nSaveKey=0;
	for (int nCnt = 0; nCnt < MAX_KEYMEMORY; nCnt++)
	{
		nSaveKey = s_Commandmemory[nCnt + 1];
		s_Commandmemory[nCnt + 1] = s_Commandmemory[nCnt];
		s_Commandmemory[nCnt] = nSaveKey;
	}
	s_Commandmemory[0] = nKey;								
}
//=====================
//�v���C���[�̂̓����蔻��
//=====================
void CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height)
{
	//�u���b�N���v���C���[�ɓ����������̔���͕ʁX�ō��Ȃ��Ƃ����Ȃ�
	if (s_Player.bDisp == true)
	{//�u���b�N���g�p����Ă��� 
	 //�u���b�N�ɑ��肪�Ԃ�������
	 //������Ԃ������ꍇ
		if (pPosOld->y + Height / 2 > s_Player.pos.y - PLAYER_HEIGHT 	//�u���b�N�̏㉺�͈͎̔w��
			&& pPosOld->y - Height / 2 < s_Player.pos.y )
		{
			//������Ԃ������ꍇ(�E�ӂɑ��肪���������ꍇ)
			if (pPosOld->x - Width / 2 >= s_Player.pos.x + PLAYER_WIDTH / 2//�O��̃v���C���[�̈ʒu���u���b�N�̈ʒu���E�ɂ���ꍇ
				&& pPos->x - Width / 2 < s_Player.pos.x + PLAYER_WIDTH / 2 //���݂̃v���C���[�̈ʒu���u���b�N�̈ʒu��荶�ɂ���(�߂荞��ł���)�ꍇ
				)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
			{//�v���C��-�ƃu���b�N������������
				pMove->x = 0;
				s_Player.pos.x = pPos->x- Width / 2 - PLAYER_WIDTH / 2;
			}
			//������Ԃ������ꍇ(���ӂɑ��肪���������ꍇ)
			else if (pPosOld->x + Width / 2  <= s_Player.pos.x - PLAYER_WIDTH / 2 	//�O��̃v���C���[�̈ʒu���u���b�N�̈ʒu��荶�ɂ���ꍇ
				&& pPos->x + Width / 2  > s_Player.pos.x - PLAYER_WIDTH / 2			//���݂̃v���C���[�̈ʒu���u���b�N�̈ʒu���E�ɂ���(�߂荞��ł���)�ꍇ
				)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
			{//�v���C��-�ƃu���b�N������������
				pMove->x = 0;
				s_Player.pos.x = pPos->x + Width / 2 + PLAYER_WIDTH / 2 ;
			}
		}
	}
}
//======================================================
//�v���C���[�̏�񃊃Z�b�g�̏���
//======================================================
void ResetPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player001.png",
		&s_pTexturePlayer);

	s_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
	s_Player.move = D3DXVECTOR3(0.0f, 0.f, 0.0f);							//�ړ��ʂ�����������
	//s_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�p�x�̏���������(���̂����g�������H)
	s_Player.nCntCounterAnim = 0;											//�J�E���^�[��������
	s_Player.nCntPtnAnim = 0;												//�p�^�[���ԍ���������//������������	
	s_Player.nDirectionMove = 0;											//�O�̎��͉E�@�P�̎��͍�����									
	s_Player.bDisp = false;													//�g�p���ɂ���
	s_Player.bIsJumping = false;											//�W�����v��ԉ����ɂ���
	s_Player.state = PLAYERSTATE_NORMAL;									//�ʏ��Ԃɂ���
	s_nTimer = 0;															//�^�C�}�[���Z�b�g
	s_Player.nCntAtk = 0;													//�U���J�E���g���Z�b�g

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffPlayer,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//�v���C���[�̏��X�V
//======================================================
static void UpdatePlayerState(void)
{
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//�v���C���[����ʒ[�ɂ������̏���
//======================================================
static void SidePlayer(void)
{
	//��ʊO�ɂ������ꍇ
	if (s_Player.pos.x > SCREEN_WIDTH - PLAYER_WIDTH/2)
	{//�n�_(X���W)����ʂ̉E�[�ɓ�������
		s_Player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
	}
	else if (s_Player.pos.x < PLAYER_WIDTH/2)
	{//�n�_(X���W)����ʂ̍��[�ɓ�������
		s_Player.pos.x = PLAYER_WIDTH/2;
	}
}
//======================================================
//�v���C���[�̃W�����v�֌W�̏���
//======================================================
static void PlayerJunp(void)
{
	VERTEX_2D*pVtx;
	if ((GetKeyboardTrigger(DIK_SPACE) == true||GetJoypadTrigger(JOYKEY_A)) && s_Player.bIsJumping == false )
	{//SPACE�L�[�������ꂽ
		s_Player.move.y += -20.0f;
		if (s_Player.bAtk==false)
		{
			//�W�����v����ۗ������[�V�����̏ꍇ�������[�V�����Ɉڍs������
			if (s_Player.nCntPtnAnim % 2 == 0 && s_Player.state != PLAYERSTATE_ATTACK)
			{
				s_Player.nCntPtnAnim++;
			}

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));	//�E���ɍ��W���w��
			pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));
			pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			//���_�o�b�t�@���A�����b�N
			s_pVtxBuffPlayer->Unlock();
		}
	}
	else if ((GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A)) && s_Player.bIsJumping == true)
	{//SPACE�L�[�������ꂽ
		s_Player.move.y -= -20.0f;
	}
}
//======================================================
//�v���C���[�̈ʒu�̍X�V
//======================================================
static void PlayerPositionUpdate(void)
{
	//�O��̈ʒu���L�^
	s_Player.posOld = s_Player.pos;

	//�ʒu���X�V
	s_Player.pos.x += s_Player.move.x;
	s_Player.pos.y += s_Player.move.y;

	//�u���b�N�̏�ɏ���Ă���ꍇ
	if (s_Player.pBlock != NULL)
	{
		//�u���b�N�̃^�C�v���Q��
		if (s_Player.pBlock->nType == 1)
		{
			//�u���b�N�̈ړ��ʂ����Z
			s_Player.pos += s_Player.pBlock->move;
		}
	}
}
//======================================================
//�v���C���[�̏�ԊǗ�
//======================================================
static void Playerstate(void)
{
	VERTEX_2D*pVtx;

	switch (s_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		s_Player.nCntState--;
		if ((s_Player.nCntState % 5) == 0)
		{
			s_Player.fPtnflashing = 1 - s_Player.fPtnflashing;
		}
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//�|���S�����_���[�W�F�ɐݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		//���_�o�b�t�@���A�����b�N
		s_pVtxBuffPlayer->Unlock();

		if (s_Player.nCntState <= 0)
		{//���G���Ԃ��������ꂽ�Ƃ�

			s_Player.fPtnflashing = 0.0f;
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			s_Player.state = PLAYERSTATE_NORMAL;

			//�|���S����ʏ�F�ɐݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���_�o�b�t�@���A�����b�N
			s_pVtxBuffPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		s_Player.nCntState--;
		if (s_Player.nCntState <= 0)
		{
			s_Player.move.x = 0;
			s_Player.state = PLAYERSTATE_NORMAL;
			//���[�h�̐ݒ�(���U���g��ʂɈڍs)
			SetGameState(GAMESTATE_FAILED);
			return;
		}
		break;
	}
}
//=======================
//�v���C���[�̃q�b�g����
//=======================
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;
	if (s_Player.bDisp==true&&s_Player.state==PLAYERSTATE_NORMAL)
	{
		s_Player.nLife -= nDamage;
		if (s_Player.nLife <= 0)
		{//�̗͂��O�ɂȂ�����
			s_Player.nLife = 0;
			s_Player.state = PLAYERSTATE_DEATH;
			s_Player.nCntState = 60;
			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				SetEffect(
					s_Player.pos + D3DXVECTOR3((float)(rand() % 20 - 10), (float)(rand() % 20 - 10), 0.0f)		//�ʒu�̐ݒ�
																													//�ړ��ʂ̐ݒ�
					, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f, 0.0f)
					, D3DXCOLOR(1.0f, 0.0f,0.0f, 1.0f)		//���_�J���[�̐ݒ�
					, 30			//���a�̑傫���̐ݒ�
					, 90
					,false
					,0);
			}
			s_Player.bDisp = false;
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}
		else
		{//�����Ă�ꍇ
			s_Player.state = PLAYERSTATE_DAMAGE;
			s_Player.nCntState = 30;//�_���[�W���Ԃ�ۂ��Ԃ�ݒ�

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�|���S�����_���[�W�F�ɐݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			s_pVtxBuffPlayer->Unlock();

			PlaySound(SOUND_LABEL_SE_HIT);
		}

	}
}
//======================================================
//�v���C���[�̍U��
//======================================================
static void PlayerAttack(void)
{
	VERTEX_2D*pVtx;
	if (s_Player.bAtk == true)
	{
		int Direction = (s_Player.nDirectionMove == 1) ? -1 : 1;

		s_Player.nCntAtk--;
		//���ƃG�t�F�N�g�Ɠ����蔻��̐ݒ�
		if (s_Player.nCntAtk == ALL_ATKTIME1 - FIRST_ATKTIME * 2)
		{//�O���ڂ̃��[�V��������
			s_Player.nCntPtnAnim++;
			SetAttack(s_Player.pos.x + 52.0f*Direction, s_Player.pos.y - 48.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f, Direction);
			Setweapon(s_Player.pos.x + 50.0f*Direction, s_Player.pos.y - 15.0f, 4.5f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ALL_ATKTIME1 - FIRST_ATKTIME * 2, true);
		}
		else if (s_Player.nCntAtk == ALL_ATKTIME1 - FIRST_ATKTIME)
		{//�񖇖ڂ̃��[�V�����Đ����ɓ����蔻��ƌ��̐ݒ�
			s_Player.nCntPtnAnim++;
			Setweapon(s_Player.pos.x - 30.0f*Direction, s_Player.pos.y - 65.0f, -0.2f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), FIRST_ATKTIME, false);
		}
		//�������I�������
		if (s_Player.nCntAtk <= 0)
		{
			s_Player.nCntCounterAnim = 0;			//�A�j���J�E���^�[�̃��Z�b�g
			s_Player.nCntAtk = 0;					//�J�E���^�[�̃��Z�b�g
			s_Player.nCntPtnAnim = 0;				//�p�^�[���̃��Z�b�g
			s_Player.bAtk = false;
		}
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.41f - (0.2f*s_Player.nDirectionMove));	//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.41f - (0.2f*s_Player.nDirectionMove));
		pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.6f - (0.2f*s_Player.nDirectionMove));
		pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.6f - (0.2f*s_Player.nDirectionMove));
		//���_�o�b�t�@���A�����b�N
		s_pVtxBuffPlayer->Unlock();
	}
}
//=====================================================
//�v���C���[����ʂ̒��S�ɗ������̏ꍇ
//=====================================================
void CenterPlayer(D3DXVECTOR3 *pPos)
{
	//�{�X�̎擾
	BOSS*pBoss = GetBoss();
	if (s_Player.pos.x >= SCREEN_WIDTH / 2&&pBoss->bUse==false&&pBoss->state!=BOSSSTATE_DEATH)
	{
		//��Q�҂̈ʒu���X�V
		s_Player.pos.x = SCREEN_WIDTH / 2;
		pPos->x -= s_Player.move.x;
	}
}
//======================================================
//�v���C���[�̎擾����
//======================================================
Player *GetPlayer(void)
{//�G�l�~�[�̃|�C���^�����Z�b�g
	return &s_Player;
}