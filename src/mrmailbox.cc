#include "mrmailbox.h"
#include "macros.h"

NAN_METHOD(hello) {
  info.GetReturnValue().Set(LOCAL_STRING("world"));
}

NAN_METHOD(New){ } 
NAN_METHOD(Unref){ } 
NAN_METHOD(Open){ } 
NAN_METHOD(Close){ } 
NAN_METHOD(IsOpen){ } 
NAN_METHOD(SetConfig){ } 
NAN_METHOD(GetConfig){ } 
NAN_METHOD(SetConfigInt){ } 
NAN_METHOD(GetConfigInt){ } 
NAN_METHOD(GetInfo){ } 
NAN_METHOD(GetVersionStr){ } 
NAN_METHOD(Connect){ } 
NAN_METHOD(Disconnect){ } 
NAN_METHOD(Heartbeat){ } 
NAN_METHOD(GetChatlist){ } 
NAN_METHOD(GetChat){ } 
NAN_METHOD(MarkNoticedChat){ } 
NAN_METHOD(GetChatIdByContactId){ } 
NAN_METHOD(CreateChatByContactId){ } 
NAN_METHOD(GetChatMedia){ } 
NAN_METHOD(GetNextMedia){ } 
NAN_METHOD(GetChatContacts){ } 
NAN_METHOD(GetFreshMsgs){ } 
NAN_METHOD(GetChatMsgs){ } 
NAN_METHOD(SearchMsgs){ } 
NAN_METHOD(SetDraft){ } 
NAN_METHOD(GetTotalMsgCount){ } 
NAN_METHOD(GetFreshMsgCount){ } 
NAN_METHOD(ArchiveChat){ } 
NAN_METHOD(DeleteChat){ } 
NAN_METHOD(SendTextMsg){ } 
NAN_METHOD(SendImageMsg){ } 
NAN_METHOD(SendVideoMsg){ } 
NAN_METHOD(SendVoiceMsg){ } 
NAN_METHOD(SendAudioMsg){ } 
NAN_METHOD(SendFileMsg){ } 
NAN_METHOD(SendVcardMsg){ } 
NAN_METHOD(CreateGroupChat){ } 
NAN_METHOD(SetChatName){ } 
NAN_METHOD(SetChatProfileImage){ } 
NAN_METHOD(IsContactInChat){ } 
NAN_METHOD(AddContactToChat){ } 
NAN_METHOD(RemoveContactFromChat){ } 
NAN_METHOD(AddAddressBook){ } 
NAN_METHOD(GetKnownContacts){ } 
NAN_METHOD(GetBlockedContacts){ } 
NAN_METHOD(GetBlockedCount){ } 
NAN_METHOD(GetContact){ } 
NAN_METHOD(MarkNoticedContact){ } 
NAN_METHOD(BlockContact){ } 
NAN_METHOD(GetContactEncrinfo){ } 
NAN_METHOD(DeleteContact){ } 
NAN_METHOD(GetMsg){ } 
NAN_METHOD(GetMsgInfo){ } 
NAN_METHOD(ForwrdMsgs){ } 
NAN_METHOD(StarMsgs){ } 
NAN_METHOD(DeleteMsgs){ } 
NAN_METHOD(MarkSeenMsgs){ } 
NAN_METHOD(ConfigureAndConnect){ } 
NAN_METHOD(IsConfigured){ } 
NAN_METHOD(StopOngoingProcess){ } 
NAN_METHOD(InitiateKeyTransfer){ } 
NAN_METHOD(ContinueKeyTransfer){ } 
NAN_METHOD(Imex){ } 
NAN_METHOD(ImexHasBackup){ } 
NAN_METHOD(CheckPassword){ } 

NAN_MODULE_INIT(InitAll) {
  EXPORT_FUNCTION(hello);
  EXPORT_FUNCTION(New);
}

NODE_MODULE(hello, InitAll)
