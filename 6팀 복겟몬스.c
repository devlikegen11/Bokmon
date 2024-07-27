#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "getch.h"
#define SUBMIT 4

void happy();
void bad();
void ready();
void Start_img();
int keyControl();

int main()
{
    srand(time(NULL));
    int SIZE = 10;
    char ch;
    char map[SIZE][SIZE];

    int x = 5, y = 5;
    int menu, user_input, run, item, rand_num;

    int boss_flag = 0, nomal_flag = 0, badflag = 0, turn = 0;
    int potion = 3, level = 1, m_shield = 10;
    int rand_shield = 0, rand_smoke = 0, rand_m_gun = 0, rand_potion = 0, shield = 0, m_gun = 0, smoke = 0;

    float hp = 3000, lv_hp_max = 3000;
    float monster_hp = lv_hp_max * (1.0 + (float)rand() / ((float)RAND_MAX / 3.0));   // 몬스터 체력
    float Boss_hp = lv_hp_max * (5.0 + (float)rand() / ((float)RAND_MAX / 8.0));      // 보스 체력
    float damage = lv_hp_max * (0.5 + (float)rand() / ((float)RAND_MAX / 3.0));       // 배틀 시 적 몬스타의 공격 데미지 변수
    float attack_damage = (hp / 2) * (1.0 + (float)rand() / ((float)RAND_MAX / 4.0)); // 배틀 시 나의 공격 데미지 변수
    float lv_up_max = lv_hp_max + lv_hp_max * (1.2 + (float)rand() / ((float)RAND_MAX / 2.5));
    float recovery = lv_hp_max * (0.3 + (float)rand() / ((float)RAND_MAX / 0.8)); // 회복량 변수

    Start_img();

    char monster[27][10] =
        {
            {"유시온"}, {"김승수"}, {"권철민"}, {"안광민"}, {"강진영"}, {"김영곤"}, {"박선후"}, {"김건"}, {"이준호"}, {"이철"}, {"이동준"}, {"황은비"}, {"조세빈"}, {"김성근"}, {"이은승"}, {"박희정"}, {"박장미"}, {"김민아"}, {"조대정"}, {"김재신"}, {"박민건"}, {"임석현"}, {"황운하"}, {"노주영"}, {"김혜빈"}, {"서훈"}, {"오은지"}};

    char bok[10] = {"복이"};
    char username[10];
    ready();
    scanf("%s", username); // 유저이름입력
    int same = 0;

    for (int i = 0; i < 28; i++) // 유저이름이 우리반 리스트에 있으면 복이로 변경
    {
        same = 0;
        for (int j = 0; j < 10; j++)
        {
            if (monster[i][j] == username[j])
            {
                ++same;
            }
        }
        if (same == 10)
        {
            for (int k = 0; k < 10; k++)
            {
                monster[i][k] = monster[i + 1][k];
            }
        }
    }

    if (level == 1)
    {
        hp = 3000;
        lv_hp_max = 3000;
        potion = 3;
        smoke = 0;
        m_gun = 0;
        shield = 0;
    }

    while (1)
    {
        printf("\n");
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                map[i][j] = ' ';
                printf(" %c ", map[i][j]);
                map[0][j] = '/';
                map[i][0] = '/';
                map[9][j] = '/';
                map[i][9] = '/';
                map[y][x] = '@';
                printf(" %c ", map[i][j]);
            }
            printf("\n");
        }

        printf("w s a d로 조작하세요\n");
        ch = getch();
        if (ch == 'w' && y > 1)
        {
            y = y - 1;
        }
        else if (ch == 'a' && x > 1)
        {
            x = x - 1;
        }
        else if (ch == 's' && y < SIZE - 2)
        {
            y = y + 1;
        }
        else if (ch == 'd' && x < SIZE - 2)
        {
            x = x + 1;
        }

        int friend = rand() % 27;
        int meet = rand() % 100;
        int flag = 0;
        monster_hp = lv_hp_max * (rand() % 2 + 1);

        if (turn > 0) // 처음 움직이지 않았을때 몬스터 등장 안하게 조절
        {
            if (meet < 30)
            {
                printf("개발원의 몬스터가 나타났다.....\n");
                flag = 1;
            }
            else if (meet > 45 && meet < 50)
            {
                printf("세상에 전설의 몬스터다!!!\n");
                flag = 2;
            }
        }

        if (flag == 1) // 일반 몬스터 조우
        {
            printf("몬스터 \"%s\"를 조우 했습니다.\n", monster[friend]);
        back: //
            printf("%s의 현재 체력 / 최대체력 %2.f / %.2f 이다.\n", username, hp, lv_hp_max);
            printf("아래의 선택지에서 대응방법을 선택하세요.\n");
            printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
            scanf("%d", &menu);
            int i = 1;

            while (i == 1)
            {
                if (menu == 1)
                {
                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                    printf("가라! %s\n", username);
                    monster_hp -= attack_damage;
                    printf("%s은(는) %s에게 %.2f만큼 피해를 입혔다.\n", username, monster[friend], attack_damage);
                    if (monster_hp > 0)
                    {
                        hp -= damage;
                        printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", monster[friend], username, damage);
                    }
                    break;
                }

                else if (menu == 2)
                {
                    printf("\n보유한 도구를 불러옵니다.\n");
                    if (shield > 0 || potion > 0 || smoke > 0 || m_gun > 00)
                    {
                        printf("방패 : 몬스터의 공격을 1회에 한하여 절반의 데미지로 피격 당합니다.\n");
                        printf("포션 : 사용자의 최대 체력에 비레해 체력을 회복합니다.\n");
                        printf("연막탄 : 전투에 한하여 적 몬스터와의 전투에서 도망갈 수 있습니다.\n");
                        printf("밍-gun : 전투 중 밍-gun으로 저격해 적을 섬멸할 수 있습니다.\n\"사용주의\"밍-gun은 허락된 사람만 사용 가능합니다.\n");
                        printf("1. 방패 \"%d개\"\n2. 포션 \"%d개\"\n3. 연막탄\"%d개\"\n4. 밍-GUN\"%d개\"\n5. 뒤로 가기\n사용할 아이템을 선택하세요.\n", shield, potion, smoke, m_gun);
                        scanf("%d", &item);

                        while (hp > 0)
                        {
                            if (item == 1)
                            {
                                if (shield > 0)
                                {
                                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                                    printf("방패를 사용합니다.(몬스터의 공격 1번을 절반의 데미지로 받습니다.)\n");
                                    --shield;
                                    hp -= damage / 2;
                                    printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", monster[friend], username, damage);
                                    printf("%s의 현재 체력: %.2f\n남은 방패: %d개\n", username, hp, shield);
                                    if (hp < 0)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("\n남아 있는 방패가 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else if (item == 2)
                            {
                                if (potion > 0)
                                {
                                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                                    recovery = lv_hp_max * ((float)(rand() % 7 + 3) / 10);
                                    printf("\"포션\"을 사용했습니다.\n\"%.2f\"만큼 회복했습니다.\n", recovery);
                                    hp += recovery;
                                    --potion;
                                    hp -= damage;
                                    printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", monster[friend], username, damage);
                                    printf("%s의 현재 체력: %.2f\n남은 포션: %d개\n", username, hp, potion);
                                    menu = 0;
                                    if (hp < 0)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("\n남아있는 포션이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else if (item == 3)
                            {
                                if (smoke > 0)
                                {
                                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                                    printf("\"n연막탄\"를 사용했습니다.\n");
                                    --smoke;
                                    printf("%s의 현재 체력: %.2f\n남은 연막탄: %d개\n", username, hp, smoke);
                                    printf("도망에 성공했습니다.");
                                    menu = 0;
                                    i = 0;
                                    break;
                                }
                                else
                                {
                                    printf("\n남아있는 연막탄이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }

                            else if (item == 4)
                            {
                                if (m_gun > 0)
                                {
                                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                                    monster_hp = -1;
                                    printf("\"밍-GUN\"을 사용했습니다.\n");
                                    --m_gun;
                                    menu = 0;
                                    i = 0;
                                    break;
                                }
                                else
                                {
                                    printf("\n남아있는 밍-GUN이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else
                            {
                                menu = 0;
                                i = 1;
                                printf("\n몬스터 \"%s\"를 조우 했습니다.\n", monster[friend]);
                                printf("%s의 현재 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
                                printf("아래의 선택지에서 대응방법을 선택하세요.\n");
                                printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
                                scanf("%d", &menu);
                                break;
                            }
                            printf("\n방패 : 몬스터의 공격을 1회에 한하여 절반의 데미지로 피격 당합니다.\n");
                            printf("포션 : 사용자의 최대 체력에 비레해 체력을 회복합니다.\n");
                            printf("연막탄 : 전투에 한하여 적 몬스터와의 전투에서 도망갈 수 있습니다.\n");
                            printf("밍-gun : 전투 중 밍-gun으로 저격해 적을 섬멸할 수 있습니다.\n\"사용주의\"밍-gun은 허락된 사람만 사용 가능합니다,\n");
                            printf("1. 방패 \"%d개\"\n2. 포션 \"%d개\"\n3. 연막탄\"%d개\"\n4. 밍-GUN\"%d개\"\n5. 뒤로 가기\n사용할 아이템을 선택하세요\n", shield, potion, smoke, m_gun);
                            scanf("%d", &item);
                            if (hp < 0)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("남아있는 아이템이 없습니다.\n");
                        continue;
                    }
                    if (hp < 0)
                    {
                        break;
                    }
                }
                else if (menu == 3)
                {
                    printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                    printf("\"도망\"을 시도 합니다.\n");
                    run = (rand() % 99 + 1);
                    if (run <= 30)
                    {
                        printf("\n\"도망\"에 성공 했습니다.\n");
                        break;
                    }

                    else
                    {
                        menu = 0;
                        printf("\n현재 몬스타의 체력은 %.2f 입니다.\n", monster_hp);
                        printf("\"도망\"에 실패 했습니다.\n");
                        hp -= damage;
                        printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", monster[friend], username, damage);
                        printf("%s의 남은 체력은 %.2f / %.2f 이다.\n", username, lv_hp_max, hp);
                        printf("몬스터 \"%s\"를 조우 했습니다.\n", monster[friend]);
                        printf("%s의 현재 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
                        printf("아래의 선택지에서 대응방법을 선택하세요.\n");
                        printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
                        scanf("%d", &menu);
                    }
                }
            }
            if (hp <= 0)
            {
                printf("\"%s\"은(는) 죽었습니다.\n", username);
                bad();
                printf("BAD ENDING\n");
                break;
            }
            else if (monster_hp <= 0)
            {
                level++;
                printf("몬스타 \"%s\"를 쓰러뜨렸습니다.\n", monster[friend]);
                hp += recovery;
                rand_potion += (rand() % 10);
                potion += rand_potion;
                rand_num = (rand() % 99 + 1);

                if (rand_num <= 1) // 밍-gun
                {
                    ++rand_m_gun;
                    m_gun += rand_m_gun;
                }
                else if (rand_num >= 2 || rand_num <= 6) // 절대무적
                {
                    ++rand_shield;
                    shield += rand_shield;
                }
                else if (rand_num >= 7 || rand_num <= 37) // 연막탄
                {
                    ++rand_smoke;
                    smoke += rand_smoke;
                }
                else if (rand_num <= 10)
                    lv_hp_max = lv_up_max;
                printf("승리 보상으로 포션을 \"%d개\"\n방패(1회 무적)를 \"%d개\"\n연막탄을 \"%d개\"\n밍-gun을 \"%d개\" 획득했습니다.", rand_potion, rand_shield, rand_smoke, rand_m_gun);
                printf("레벨 업!\n%s의 레벨이 \"%d\" HP가 %.2f 만큼 회복되고 최대치가 증가했습니다.\n", username, level, recovery);
                lv_hp_max = lv_up_max;
                int rand_potion = 0, rand_shield = 0, rand_smoke = 0, rand_m_gun = 0;
                continue;
            }
            else if (monster_hp > 0)
            {
                goto back;
            }
        }

        if (flag == 2) // 보스 몬스터 조우
        {
            printf("보스 몬스타 \"%s\"를 조우 했습니다.\n", bok);
        back2:
            printf("%s의 현재 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
            printf("아래의 선택지에서 대응방법을 선택하세요.\n");
            printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
            scanf("%d", &menu);
            int i = 1;

            while (i == 1)
            {
                if (menu == 1)
                {
                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                    printf("가라! %s\n", username);
                    Boss_hp -= attack_damage;
                    printf("%s은(는) %s에게 %.2f만큼 피해를 입혔다.\n", username, bok, attack_damage);
                    if (Boss_hp > 0)
                    {
                        hp -= damage;
                        printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", bok, username, damage);
                    }
                    break;
                }

                else if (menu == 2)
                {
                    if (shield > 0 || potion > 0 || smoke > 0 || m_gun > 00)
                    {
                        printf("\n보유한 도구를 불러옵니다.\n");
                        printf("방패 : 몬스터의 공격을 1회에 한하여 절반의 데미지로 피격 당합니다.\n");
                        printf("포션 : 사용자의 최대 체력에 비레해 체력을 회복합니다.\n");
                        printf("연막탄 : 전투에 한하여 적 몬스터와의 전투에서 도망갈 수 있습니다.\n");
                        printf("밍-gun : 전투 중 밍-gun으로 저격해 적을 섬멸할 수 있습니다.\n\"사용주의\"밍-gun은 허락된 사람만 사용 가능합니다.\n");
                        printf("1. 방패 \"%d개\"\n2. 포션 \"%d개\"\n3. 연막탄\"%d개\"\n4. 밍-GUN\"%d개\"\n5. 뒤로 가기\n사용할 아이템을 선택하세요.\n", shield, potion, smoke, m_gun);
                        scanf("%d", &item);

                        while (hp > 0)
                        {
                            if (item == 1)
                            {
                                if (shield > 0)
                                {
                                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                                    printf("방패를 사용합니다.(몬스터의 공격 1번을 절반의 데미지로 받습니다.)\n");
                                    --shield;
                                    hp -= damage / 2;
                                    printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", bok, username, damage);
                                    printf("%s의 현재 체력: %.2f\n남은 방패: %d개\n", username, hp, shield);
                                    if (hp < 0)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("\n남아 있는 방패가 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else if (item == 2)
                            {
                                if (potion > 0)
                                {
                                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                                    recovery = lv_hp_max * ((float)(rand() % 7 + 3) / 10);
                                    printf("\"포션\"을 사용했습니다.\n\"%.2f\"만큼 회복했습니다.\n", recovery);
                                    hp += recovery;
                                    --potion;
                                    hp -= damage;
                                    printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", bok, username, damage);
                                    printf("%s의 현재 체력: %.2f\n남은 포션: %d개\n", username, hp, potion);
                                    if (hp < 0)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("남아있는 포션이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else if (item == 3)
                            {
                                if (smoke > 0)
                                {
                                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                                    printf("\"n연막탄\"를 사용했습니다.\n");
                                    --smoke;
                                    printf("%s의 현재 체력: %.2f\n남은 연막탄: %d개\n", username, hp, smoke);
                                    printf("도망에 성공했습니다.");
                                    menu = 0;
                                    i = 0;
                                    break;
                                }
                                else
                                {
                                    printf("\n남아있는 연막탄이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else if (item == 4)
                            {
                                if (m_gun > 0)
                                {
                                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                                    Boss_hp = -1;
                                    printf("\"밍-GUN\"을 사용했습니다.\n");
                                    --m_gun;
                                    printf("탕!\n몬스터가 소멸되어 전투를 중지합니다.\n");
                                    menu = 0;
                                    i = 0;
                                    break;
                                }
                                else
                                {
                                    printf("\n남아있는 밍GUN이 없습니다.\n다시 선택해주세요.\n");
                                }
                            }
                            else
                            {
                                menu = 0;
                                i = 1;
                                printf("\n보스 몬스타 \"%s\"를 조우 했습니다.\n", bok);
                                printf("%s의 현재 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
                                ;
                                printf("아래의 선택지에서 대응방법을 선택하세요.\n");
                                printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
                                scanf("%d", &menu);
                                break;
                            }
                            printf("\n방패 : 몬스터의 공격을 1회에 한하여 절반의 데미지로 피격 당합니다.\n");
                            printf("포션 : 사용자의 최대 체력에 비레해 체력을 회복합니다.\n");
                            printf("연막탄 : 전투에 한하여 적 몬스터와의 전투에서 도망갈 수 있습니다.\n");
                            printf("밍-gun : 전투 중 밍-gun으로 저격해 적을 섬멸할 수 있습니다.\n\"사용주의\"밍-gun은 허락된 사람만 사용 가능합니다,\n");
                            printf("1. 방패 \"%d개\"\n2. 포션 \"%d개\"\n3. 연막탄\"%d개\"\n4. 밍-GUN\"%d개\n5. 뒤로가기\n사용할 아이템을 선택하세요\n", shield, potion, smoke, m_gun);
                            scanf("%d", &item);
                            if (hp < 0)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("\n사용 가능한 아이템이 없습니다.\n");
                        menu = 0;
                        continue;
                    }
                }
                else if (menu == 3)
                {
                    printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                    printf("\"도망\"을 시도 합니다.\n");
                    run = (rand() % 99 + 1);
                    if (run <= 30)
                    {
                        printf("\n\"도망\"에 성공 했습니다.\n");
                        break;
                    }
                    else
                    {
                        menu = 0;
                        printf("\n현재 보스의 체력은 %.2f 입니다.\n", Boss_hp);
                        printf("\"도망\"에 실패 했습니다.\n");
                        hp -= damage;
                        printf("%s은(는) %s에게 %.2f만큼 피해를 입었다.\n", bok, username, damage);
                        printf("%s의 남은 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
                        printf("몬스터 \"%s\"를 조우 했습니다.\n", monster[friend]);
                        printf("%s의 현재 체력은 %2.f / %.2f 이다.\n", username, lv_hp_max, hp);
                        ;
                        printf("아래의 선택지에서 대응방법을 선택하세요.\n");
                        printf("1: 배틀\n2: 도구사용\n3: 도망치기\n");
                        scanf("%d", &menu);
                    }
                }
            }
            if (hp <= 0)
            {
                printf("\"%s\"은(는) 패배했습니다.\n", username);
                printf("태초마을로 돌아가세요.\n");
                level = 1;
                hp = 3000;
                lv_hp_max = 3000;
                potion = 3;
                smoke = 0;
                m_gun = 0;
                shield = 0;
                continue;
            }
            else if (Boss_hp <= 0)
            {
                printf("몬스타 \"%s\"를 쓰러뜨렸습니다.\n", bok);
                happy();
                printf("해피해피!!!!");
                break;
            }
            else if (Boss_hp > 0)
            {
                goto back2;
            }
        }
        else
        {
            printf("\n---%s---\tLV %d", username, level);
            printf("\n현재 체력: %.2f, 최대체력: %2.f\n", hp, lv_hp_max);
        }
        turn++;
        if (badflag == 1)
        {
            break;
        }
    }
    return 0;
}

void Start_img()
{
    printf("\n\n");
    printf("                        [ 조작법 ]\n\n");
    printf("                    이동: W, A, S, D\n");
    printf("                    선택: 엔터(ENTER)\n\n\n\n\n\n\n");
    printf("              엔터(Enter)를 누르면 시작합니다.\n\n\n");
    while (1)
    {
        if (keyControl() == SUBMIT)
        {
            break;
        }
    }
}

int keyControl()
{
    char temp = getch();
    if (temp == '\n') // 엔터가 선택 버튼
    {
        return SUBMIT;
    }
}

void happy()
{
    printf("\n");
    printf("⠀⠀⠀⠀⠀⠀⢰⠑⠤⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢀⢄⡀⠃⠅⡡⡀⣖⢵⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠐⡐⠌⠪⠴⡍⡔⣗⢕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠢⢌⠌⠠⢘⠪⡪⣸⢸⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠡⡑⡑⢦⢣⠣⡣⡣⣓⢮⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⡢⡠⢢⡀⠑⢕⢕⢇⢇⢗⢥⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠑⠌⡂⠌⡞⢬⠪⡪⡳⡱⡳⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠨⠪⠸⠠⠌⡪⡪⡝⡼⣸⢸⢜⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠝⡔⡪⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⡬⡈⡔⡘⡪⡪⡪⡎⣎⢎⢎⢎⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠨⠪⠨⡂⡎⡆⠀⠀⠠⠠⣠⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠈⠢⡡⢈⢡⢜⢸⣜⢬⢣⢣⢣⣣⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢱⠵⢕⡄⡢⡨⡜⡎⠃⠁⠀⠀⠀⠀⢀⢔⠍⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢐⢐⢘⠂⠣⠣⣪⢪⢣⢣⡣⡳⣣⢣⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢫⢲⢣⢙⠼⠱⢍⢀⠀⠀⠀⠀⠀⣠⡫⡚⡁⡇⠃⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⢡⠤⢗⠈⢲⢐⢎⢇⢗⢇⢯⢮⡳⣕⢢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⡜⣜⢼⣸⠈⠣⠃⠉⠀⠀⠀⣠⢞⢵⡹⡜⢌⠆⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠱⠐⠑⠄⠁⢥⢳⢱⢱⡓⡧⡳⣕⢧⡣⡄⠀⠀⠀⠀⠀⠀⠀⠀⠜⠼⠜⠚⠈⠁⠀⠀⠀⠀⢀⡴⣏⢗⣝⢝⢆⠱⡰⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠩⣈⣂⡑⣑⢑⢵⢱⡫⣺⢪⡳⡵⣍⢗⢄⠀⠀⠀⡀⡔⡕⣕⠍⠀⠀⠀⠀⠀⢀⡤⣺⡳⡹⣜⣝⢝⡆⡌⡏⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⡂⣢⠑⠑⡕⡇⡏⡧⣳⢹⢜⢧⡫⡪⡲⡝⡜⡜⡼⡜⠀⠀⣀⡠⣴⡪⣗⢝⢮⢎⢯⠮⣪⢆⠲⠉⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠢⢥⠱⡈⠈⠎⡇⡗⣝⢎⡧⠣⡣⡣⡣⡫⡮⣳⣝⣖⡯⣞⢞⣕⢧⡳⡝⡵⡹⠣⡣⠢⠂⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⡌⠣⢡⠔⡈⡊⢃⠐⠠⢀⠑⢝⢜⢽⢕⣗⢗⡽⡪⡳⡕⢇⠿⡘⣪⠑⠗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢩⠅⠱⠈⡀⠂⠄⠡⠀⢂⢈⢊⢃⠯⣎⢗⠹⡘⢕⢍⠖⠕⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⣀⠆⠃⠀⠂⠐⢀⠈⡀⡂⡢⣩⢍⡆⠇⠕⠚⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢀⢀⢀⢀⡀⣀⠀⡢⢕⢄⢈⠄⠅⢌⢐⢌⢂⢆⠎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⢀⠤⣘⠔⢖⠱⡸⡸⡸⡡⡱⣱⡫⣎⡎⡮⣊⠢⡢⡢⢕⠴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⡀⠂⢑⢈⠆⢇⠪⡊⢆⢗⡬⡇⣕⢇⢇⢻⡺⡵⣝⡽⠜⢜⡼⣼⣈⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠈⠢⠑⡀⢂⠅⡅⡇⢕⢑⠵⠸⡸⡸⡸⡸⡸⡣⣱⢰⠀⠀⠱⢫⣸⡲⣕⣟⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⡈⠠⠈⡐⠄⡯⡊⠣⡱⠱⢕⢣⠣⡱⡑⢇⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠈⠃⠈⠀⠀⢊⠠⠨⠨⡌⡪⣊⡢⠱⡑⠼⠐⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠄⠡⠀⡐⠈⡐⠀⡢⡀⠍⢐⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠓⠈⣄⣂⠀⠋⢐⡠⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("                        !! 해      피      엔      딩 !!");
}

void ready()
{
    printf("\n");
    printf("⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⢀⠀\n");
    printf("⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⣀⠤⠒⠒⠲⢢⣄⡀⠀⠀⡀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠀⠀⠀\n");
    printf("⠈⠀⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠒⣿⢶⣴⡶⠆⢀⠱⣹⣿⡆⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⡀⠀⢀⠀⠀⠈⠀⠈\n");
    printf("⠀⡀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⠛⠛⢯⢫⠣⡻⡙⡝⢟⢻⠷⡄⠀⠁⠀⠀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠁⠀⠐\n");
    printf("⢀⠀⠀⠄⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠠⠀⠀⣈⡲⢜⣍⣪⡾⡏⣁⣀⠀⠀⠂⠀⠈⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠀⠂⠀\n");
    printf("⢀⠀⢀⠀⠠⠀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⢀⡤⣏⢧⢤⢻⣎⡔⡵⡼⡱⡢⡳⡦⣄⠐⠀⠐⠈⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠠⠐⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⡀⠄⠀⠀⡀⠀⢀⠀⠀⡀⠀⢠⢮⡹⡼⣾⢣⣣⣛⣮⣚⢮⢾⢮⣞⢯⡫⣺⣣⠀⠀⡀⠄⠐⠈⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠀⠀⢀⠀⠄\n");
    printf("⠀⠁⠀⠁⠀⠀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠈⠷⣱⣴⢾⠷⠀⠀⠰⡾⢯⣻⡽⣺⡷⠝⠎⠊⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠈⠀⠀⠀⠀\n");
    printf(" ⠀ ⠀⠂⠀⠂⠈⠀⠀⠀⠀⡀⠀⢀⠀⠀⠀⠀⠀⠀⣻⡝⠙⣏⠟⠊⢳⢽⣯⡟⠀⠀⠀⠀⡀⠐⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⠐⠀⠐⠈\n");
    printf("⠀⠈⠀⠀⠄⠀⠀⠄⠀⠁⠀⠀⠀⡀⠀⠀⠁⠀⠁⠀⠽⣃⣀⢪⢹⠄⠨⡺⡻⡇⠀⠀⠐⠀⠈⠀⠀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠄⠂⠀⠠⠀\n");
    printf("⠀⠁⢀⠠⠀⠐⠀⠀⠠⠐⠀⠁⠀⠀⠀⠈⠀⠀⠂⠀⠀⡺⢕⣽⠁⠙⣫⣪⣫⠀⠀⠐⠀⢀⠀⠁⠀⠄⠀⠀⠀⠀⡀⠀⢀⠀⠀⡀⠀⢀⠀⠀⠀⠀⡀⠀⠄⠀\n");
    printf("⠈⢀⠀⠀⠀⢀⠀⠂⠀⠀⡀⠀⠄⠂⠁⠀⠈⠀⠀⠶⣩⣻⡷⠿⠂⠸⢷⠷⢺⡳⠀⠀⠄⠀⠀⠠⠀⠀⡀⠐⠈⠀⠀⠀⠀⢀⠀⠀⡀⠀⢀⠀⠁⠀⠀⠀⢀⠀\n");
    printf("⠀⠀⠀⡀⠈⠀⠀⠀⠀⠁⠀⠀⠀⠀⡀⠄⠂⠀⠂⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⢀⠀⠀⠂⠈⠀⠀⠐⠀⠀⠄⠀⠈⠀⠀⠀⢀⠀⠀⡀⠀⠀⠂⠁⠀⠀⢀\n");
    printf("⠀⠀⠀⠀⡀⠀⠄⠐⠀⠀⠁⠀⠁⠀⠠⠀⠀⠂⠀⠀⠠⠐⠀⠀⠄⠀⠂⠁⠀⠈⠀⠐⠀⠁⠀⠀⠀⠂⠀⠠⠀⠀⠄⠂⠀⠈⠀⠀⠀⢀⠀⠀⠐⠀⢀⠀⠁⠀\n");
    printf("⢀⡒⢒⣒⣒⣒⣚⣒⣒⣚⣒⣒⣒⣓⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣓⣒⣓⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣚⣒⣒⣒⣒⣒⣒⣒⠢⡀⠐\n");
    printf("⢸⡯⡇⠀⢐⡲⢖⠀⣀⠄⢐⢰⠁⡆⠀⠀⠂⠀⠐⠀⠀⡤⠤⠤⢰⢀⠤⣀⠐⡆⢰⠀⠀⠀⠤⠤⡄⡆⢀⣤⣤⣤⡀⠀⠀⡀⠀⡀⠀⢀⠀⠀⡀⠀⡀⡇⡇⠀\n");
    printf("⢸⡯⡇⠀⡉⠑⠉⠁⣿⠒⢻⢸⢐⠋⠋⠛⠂⠀⠀⠂⠀⠚⢒⠒⢸⠘⡒⠉⣈⠃⡚⠙⠙⠒⠀⡝⠀⡗⠘⠁⣾⠏⠁⢀⠀⠀⡀⠀⡀⠀⢀⠀⠀⠀⠀⡇⡇⠀\n");
    printf("⢸⡯⡇⠀⠓⠒⠒⠂⠁⠉⠈⠘⠘⠒⠒⠒⠂⠀⠂⠀⠀⠒⠚⠒⠘⠘⠙⠘⠈⠃⠓⠒⠒⠒⠉⠀⠀⠃⠀⠀⠚⠂⠀⠀⢀⠀⠀⡀⠀⢀⠀⠀⡀⠀⠀⡇⡇⠀\n");
    printf("⠘⢧⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣥⣭⣭⣬⣭⣥⣭⣭⣬⣥⣭⡴⠃⠀\n");
    printf("--------------------------------------------------------------------\n");
    printf("                     게임을 시작하겠습니다.\n");
    printf("                      이름을 입력해주세요 \n");
    printf("--------------------------------------------------------------------\n");
}

void bad()
{
    printf("\n");
    printf("⢮⢳⡹⣪⡳⡝⡮⡳⣝⢮⢳⢝⢮⡫⣞⢵⡫⣞⢽⢵⣫⢯⡳⡝⡮⡳⡹⣪⢯⢯⣫⢯⢯⢯⡯⣟⡮⡯⣺⢝⣵⡫⡯⣞⢽⡹⣝⢽⢵⡫⣗⢯⣫⢞⡽⣝⢮⡫⣞⣝⢮\n");
    printf("⡳⣝⢮⣣⢗⡽⣪⢯⣺⡪⡯⣫⡳⣝⣞⡵⡯⣞⢝⢕⢑⢅⡒⡔⡢⡑⡌⡢⡑⡅⢕⢫⢯⢯⢯⣗⡯⣯⡺⣝⣞⣞⣽⡺⣽⡺⣝⡽⣕⢯⣞⡽⣪⢗⡽⣺⢵⣫⢞⡮⣫\n");
    printf("⡽⣪⢗⣗⢯⢯⢞⣗⣗⡽⡽⣵⣻⣪⡞⡎⠣⡂⡢⢊⠔⡡⢊⠔⡑⢌⢆⠣⡪⡨⢢⠡⡓⢯⣟⡮⡿⣵⣻⣕⣗⣗⣗⡯⣗⡯⣗⡯⣯⣳⡳⡽⡽⣝⡽⡮⣳⢽⣝⣞⢗\n");
    printf("⢾⢽⣝⡮⡯⡯⡯⣞⡮⣯⣻⣺⡺⠪⠨⢂⠕⡐⢄⢑⢐⠌⡂⠕⡨⢂⠆⡣⠪⡘⡔⡱⢸⢘⠼⡽⣝⣷⣳⣗⣗⣗⢗⡯⡷⡯⣗⣯⣗⢷⢽⢽⢽⢮⣗⢯⡳⡯⣞⡮⣯\n");
    printf("⣽⡳⣗⡯⣯⢯⣟⣗⡯⣗⣗⠗⢅⢑⠅⢅⢂⠪⡐⠌⡂⡪⠐⢅⢊⠔⡡⢊⠬⢨⠪⡸⡐⡅⡣⢫⡻⣺⣺⢞⡷⡯⣗⢯⢯⣻⢽⣺⣺⢽⢽⢽⣝⢷⢽⢵⢯⢯⣗⣟⣞\n");
    printf("⡮⣟⣗⣯⢯⢷⣳⣗⢿⢽⠪⡈⡢⢂⠪⡐⢔⠡⢊⠌⡢⠨⡊⢔⢐⠅⢌⠢⡡⠱⡨⡊⡆⡕⢜⢰⢩⢣⢫⢟⢽⣻⡽⣯⣻⣺⢽⣺⢽⢽⢽⢽⣺⢽⢽⢽⣝⣗⣗⣗⢷\n");
    printf("⡯⣟⣞⣗⡿⡽⣞⣞⣯⠫⡈⢆⡪⡰⡱⡨⣂⠪⡐⡡⠨⡂⡪⢐⢐⠅⡑⢌⠢⡑⠔⡌⡪⡪⢌⡲⡱⡱⡱⡱⣵⢯⣟⣷⣻⣞⡽⣞⣯⢿⢽⣽⣺⢽⢽⢵⣳⣣⣗⣗⡯\n");
    printf("⣽⣳⣻⣺⡽⡯⣟⣾⣺⢕⠸⡈⠂⠌⠠⠁⠅⠣⣣⣪⠨⡂⢌⠢⠡⡊⢌⢂⢅⢊⢌⠢⡣⡱⣱⢱⢕⢕⠵⡝⡯⣟⣷⡯⣿⣽⣯⣟⡾⣽⢯⡾⣞⣯⢿⢽⣺⣺⣺⢮⢯\n");
    printf("⣗⣟⡾⣵⣻⡽⣗⣷⣫⢷⡱⡀⠅⠨⢀⠡⢀⡳⡕⠅⠙⢜⢄⠅⢕⠨⡂⡢⠢⡑⡐⢕⢜⢜⢎⢮⢪⢣⣫⣺⣽⣿⣳⣿⣻⡾⣷⢿⣽⡽⣽⣽⣻⣞⣯⣟⣷⣻⣺⢽⢽\n");
    printf("⣿⣺⡽⣗⣟⡾⡽⡾⣽⣻⣺⡄⡂⢕⠕⡱⠱⡹⡨⠀⡅⡄⡇⢇⢑⠌⡂⡪⠨⠢⡱⡱⡕⣕⢝⡜⡼⣸⡺⣯⣷⢿⣽⢾⣯⣟⣿⣻⡷⣿⡽⣞⣷⣯⡷⣟⣾⣳⡯⣿⢽\n");
    printf("⣻⢾⡽⣯⢷⣟⣯⣟⡷⣻⣺⣗⣆⡊⢆⠪⢨⠨⡊⢎⢊⠢⢊⠢⢑⠈⠢⠈⠌⠌⠠⢘⢮⡪⡓⢝⢘⢸⢾⣻⣽⡿⣽⣟⣷⣟⣷⣟⣿⢯⣿⡽⡾⣞⣿⡽⣷⣻⣽⢯⡿\n");
    printf("⡯⣯⢿⣽⣻⣞⡷⣯⢿⣽⣳⣗⡷⠅⠑⡈⠐⠐⡀⠂⠄⡈⠀⠄⠠⠈⠠⠨⡈⠄⠁⡐⠨⢪⢇⠂⢅⢎⣯⣻⣽⣿⣽⣾⢿⡾⣷⢿⡾⣿⣯⣿⣻⣽⢷⣟⣯⡿⣞⣿⡽\n");
    printf("⡯⡯⣿⣺⣗⣯⢿⣽⣳⠗⡙⢎⠂⠨⠀⢂⠈⠄⠐⡀⢂⠀⡁⠄⠁⡨⡘⠔⠀⠂⢁⠀⢂⠁⠇⣪⢮⣟⣿⣽⡷⣿⢾⣯⣿⣻⣟⣯⣿⣻⣾⣻⣽⣾⢿⡽⡷⣟⣯⡷⣿\n");
    printf("⡽⡽⣺⢵⣟⡾⡫⠊⡂⠡⢐⠠⢈⠐⢈⠠⠐⠈⠠⠀⢂⠠⢀⠂⠕⢜⢜⠠⠈⡀⠂⠐⠀⠌⡂⢝⣟⣯⣷⣿⣻⣟⣿⢷⣿⣽⣯⡿⣾⣻⡾⣯⣿⢾⣯⢿⣽⣻⣗⣿⢽\n");
    printf("⡺⡽⣝⢷⢝⣇⠂⢅⢢⢑⠠⡂⢢⣨⢤⣢⡮⣼⣔⢑⠠⠁⠂⡁⠐⡀⠄⢀⠂⠠⠈⡀⠡⠐⢌⢂⢻⣽⣷⢿⣽⣯⣿⣻⡷⣿⢾⣟⣯⣿⣽⢿⡾⣿⣻⣟⣾⣳⣟⡾⣯\n");
    printf("⢽⢽⣺⢽⣝⣞⠌⠄⠅⠅⡂⢌⠸⢽⣻⣽⡽⣞⣯⣷⣄⠌⡐⠀⠂⠠⠐⠀⠐⡀⠂⡀⢂⠕⡁⡢⢑⠝⣟⣿⣽⣾⣯⣿⣻⣟⣿⣽⢿⡾⣯⣿⣻⣿⣻⣯⣷⣟⣾⣻⣽\n");
    printf("⣯⣟⡾⡯⣾⣺⠠⠁⠅⠅⡂⠅⠌⣺⣻⣗⣟⡿⣯⣷⣟⣧⡢⡨⠐⢀⠡⢈⠠⠀⢂⠐⡐⢀⠂⡂⡕⡜⡜⢜⠨⢘⠘⠹⠹⡺⣿⢾⣿⣻⡿⣾⣻⣾⣟⣯⣿⡿⣞⣿⣺\n");
    printf("⣳⣗⡿⣽⣳⡇⠅⠡⠡⢁⠂⡡⠡⣯⡷⣗⣯⣿⣻⣽⠫⢊⠌⢄⠑⢔⢄⠠⢀⢂⢂⡂⡢⢢⢱⢪⠪⠊⠌⡐⠐⡀⠌⠠⠁⡐⡜⡯⣿⣽⣟⣿⣽⣷⢿⣿⣽⣿⢿⣯⡷\n");
    printf("⣗⢷⣻⣳⣗⡇⠅⠡⠈⠄⡂⡂⣽⣟⣯⡷⣿⢾⢫⠢⡁⠐⢅⠂⠌⡘⡜⢜⠔⡕⡱⠸⡘⠜⠈⠄⡁⢁⠁⡀⠂⢀⠐⠀⡌⢎⠪⡸⡘⣞⣯⡿⣷⢿⣻⣷⢿⣽⣿⣟⣿\n");
    printf("⡷⣟⣷⣻⢮⡇⠅⠡⠨⠐⡁⣿⣻⣽⣳⣻⡿⡍⡢⡑⠠⠈⢢⠨⠐⠠⠱⡀⠂⠠⠐⠀⠄⠂⠁⠠⠀⠠⠀⠠⠐⠀⡀⢅⢊⠢⡑⢌⠎⡆⣟⣿⣻⣿⣻⣽⡿⣯⣷⣿⢿\n");
    printf("⡽⣳⢕⡷⣝⢎⠄⠅⠌⡐⠌⡺⣻⢽⣞⡷⡏⡢⢒⢌⠐⠈⠐⡄⠅⠡⢑⠐⢅⠀⠂⠁⠠⠀⠁⠄⠈⡀⠐⠀⠐⢀⠀⢆⠅⠕⢌⠢⡱⢱⠸⡽⣿⢾⣟⣯⣿⣟⣿⣾⢿\n");
    printf("⣟⣞⡽⡮⣳⡣⢂⠁⡂⢐⢁⠪⣳⡳⣕⢏⠢⡊⡢⠢⢈⠀⠂⡢⠡⠡⠡⢑⠄⢅⠐⡈⡠⡀⡁⠀⠂⠀⠄⠁⢈⠀⠠⡑⢌⢊⠢⡑⢌⠪⡪⡪⣿⣿⣻⣽⣷⢿⡷⣿⣟\n");
    printf("⣕⢷⢽⢝⡷⣝⢀⠂⡂⠂⡂⠌⢮⡻⡘⢔⢑⠌⡢⡑⡀⠂⠡⡢⠡⡁⠌⡀⠪⢐⢢⢃⠅⢕⠅⠁⡈⠀⠐⠈⠀⡀⢂⠪⡐⡡⢑⠌⡢⠱⡘⡔⡕⣿⣟⣿⣾⢿⣟⣯⣿\n");
    printf("⣗⢯⡳⡯⣞⡵⠐⡀⢂⠡⠠⢑⠨⢪⠨⡂⢆⠕⢌⠆⡀⠂⢕⠡⡣⠐⡐⠠⢑⢐⠨⡢⢡⠣⠂⠁⠀⡀⢁⠐⢀⠐⡀⡊⢆⠊⢔⠡⡊⢌⠪⡘⡜⣜⣿⣻⣾⣟⣿⡽⣟\n");
    printf("⣝⣗⢯⢯⣳⢝⠄⢂⠐⡐⠈⠄⡂⠅⡃⠣⢕⡘⠔⡅⠄⠢⡑⡌⠜⡔⠨⡈⡂⠢⢑⢱⢘⢔⢐⢄⢁⠀⠄⢀⠐⡀⡂⠌⡢⡑⢅⢊⢌⢢⠣⠱⠑⢝⣿⢿⣾⢿⣾⣻⣿\n");
    printf("⣗⡽⡽⣝⡮⣗⢈⠄⠂⠄⡁⠂⢄⢑⠀⡁⠂⡑⢵⣑⠀⡁⠑⡘⡌⡪⢢⠢⢊⠨⠀⡂⢕⢌⢢⠑⠁⡀⠄⠀⡂⠄⡐⠠⢱⢰⡑⠔⠁⠂⡈⠠⠑⢈⢺⡿⣟⣿⣽⣟⣾\n");
    printf("⡳⡽⡽⣺⢝⣞⡄⠂⡁⠂⠄⡁⢂⢂⠂⠠⠡⣸⢵⡗⠄⢀⠂⢎⠢⡊⡂⠨⡢⡂⢁⠄⢂⠱⡡⠁⠠⠀⡀⠁⠄⢂⠐⡈⢔⠽⣮⠠⠈⠀⠄⠀⠂⢂⠐⠽⣿⣻⣷⢿⣯\n");
    printf("⡺⡽⣝⣮⡻⣚⢮⡐⢀⠁⡂⢐⠀⡂⡈⢄⢵⣝⣗⣏⠂⡀⠌⠆⢇⢊⠠⢘⠐⠕⡄⢂⠐⢐⠨⡂⠄⠂⢀⢈⠐⡀⠂⢌⢢⢑⢝⣗⠄⠁⠠⠈⠠⠐⢈⠈⢽⢿⣽⡿⣷\n");
    printf("⡯⡯⣳⡳⡽⣹⣕⢯⢖⣔⠠⠐⡀⡢⣰⢜⣗⣗⣗⣗⠀⠄⠐⠀⠄⢀⠀⠠⠀⡁⠐⡡⠈⠄⠐⡈⢢⠐⠀⠄⠂⠄⡁⢆⢕⡴⣕⣝⣗⠌⠀⠐⠀⠂⠠⠨⢈⢿⣯⣿⣽\n");
    printf("⢾⡺⡵⣹⢎⡗⣗⢯⣻⡪⣟⢼⢜⡮⣗⡯⣗⣗⣗⡇⠂⠄⠁⠄⠂⠀⠄⠁⡀⠄⠠⠐⠡⡁⠂⠂⢂⠱⡐⡈⠌⡀⢂⢗⣯⡯⡷⡯⡾⡅⠂⢁⠈⡀⠂⠡⢀⢳⣟⣷⣿\n");
}
