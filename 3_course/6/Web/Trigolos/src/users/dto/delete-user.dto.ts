import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class DeleteUserDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  readonly email: string;
}
