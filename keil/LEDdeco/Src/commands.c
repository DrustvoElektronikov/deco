#include "stm32f0xx.h"                  // Device header
#include "commands.h"

/* Flash storage for settings at absolute address */
const CMD_t settings_Store[CMD_LEN] __attribute__((at(FLASH_STORE_ADR)));



/**

   */
void cmd_store(char *argstr_buf, uint8_t del, uint8_t echo)
{
	int x,i;
	HAL_StatusTypeDef FLstatus;
	FLASH_EraseInitTypeDef eraseinit;
	uint32_t PageError;
	uint32_t stadr;
	uint64_t buf;
	uint32_t fladr;
	uint8_t *adr;
	

	FLstatus = HAL_FLASH_Unlock();  
	FLstatus =  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, fladr, buf);

//			// Erase backup sector
//			eraseinit.NbPages = 1;
//			eraseinit.PageAddress = FLASH_BACKUP_ADR;
//			eraseinit.TypeErase = TYPEERASE_PAGES;
//			FLstatus = HAL_FLASHEx_Erase(&eraseinit, &PageError);   
//			
//			// copy store to backup
//			for (i = 0; i< SETTINGS_CATLEN; i++)
//			{
//				adr = (uint8_t *)&tmp_settings;
//				memcpy(adr, &settings_Store[i], sizeof(settings_t));
//				fladr = FLASH_BACKUP_ADR+sizeof(settings_t)*(i);
//				for (stadr = 0; stadr<(sizeof(settings_t)/8); stadr++)
//				{
//					memcpy(&buf, adr, 8); 
//					FLstatus =  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, fladr, buf);
//					adr+=8;
//					fladr+=8;
//				}

//		  }
//			if (echo)
//			{
//			  snprintf(izp, 32, "Backup... status %d\n\r", FLstatus); 
//		    USB_write((uint8_t *)izp, strlen(izp));
//			}
//			// erase store 
//			eraseinit.NbPages = 1;
//			eraseinit.PageAddress = FLASH_STORE_ADR;
//			eraseinit.TypeErase = TYPEERASE_PAGES;
//			FLstatus = HAL_FLASHEx_Erase(&eraseinit, &PageError);   
//			
//			// and write to it from new data and backup

//			for (i = 0; i< SETTINGS_CATLEN; i++)
//			{
//        if (i == x) // actual location is written with new data
//				{
//					if (del == 1) // delete
//					{
//						// do nothing, keep erased flash
//					}
//					else
//					{							
//						adr = (uint8_t *)&settings;
//						fladr = FLASH_STORE_ADR+sizeof(settings_t)*x;
//						for (stadr = 0; stadr<(sizeof(settings_t)/8); stadr++)
//						{
//							memcpy(&buf, adr, 8); 
//							FLstatus =  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, fladr, buf);
//							adr+=8;
//							fladr+=8;
//						}
//					}
//				}  // if i==x
//				else
//				{
//					adr = (uint8_t *)&tmp_settings;
//					memcpy(adr, &backup_settings_Store[i], sizeof(settings_t));
//					fladr = FLASH_STORE_ADR+sizeof(settings_t)*(i);
//					for (stadr = 0; stadr<(sizeof(settings_t)/8); stadr++)
//					{
//						memcpy(&buf, adr, 8); 
//						FLstatus =  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, fladr, buf);
//						adr+=8;
//						fladr+=8;
//					}
//					
//				}
//			}  /*  for ... */
//			if (echo)
//			{
//				snprintf(izp, 32, "Writing... status %d\n\r", FLstatus); 
//				USB_write((uint8_t *)izp, strlen(izp));
//			}


//			FLstatus = HAL_FLASH_Lock();  
//		}
//  }
}



